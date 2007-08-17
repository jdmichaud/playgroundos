// Those are the basic asm functions needed for a start

#include "asm.h"

/*
 * Memory access
 * farpeekl
 * farpokeb
 */

/* FAR_PEEKx
    read a byte (or word or dword) on a given memory location using another 
    segment than the default C data segment. There's unfortunately no 
    constraint for manipulating directly segment registers, so issuing the 
    'mov <reg>,<segmentreg>' manually is required.
*/

dword farpeekl(word sel,void *off)
{
  dword ret;
  asm("push %%fs;mov %1,%%fs;"
      "mov %%fs:(%2),%0;"
      "pop %%fs":"=r"(ret):"g"(sel),"r"(off));
  return ret;
}

/* FAR_POKEx
    write a byte (or word or dword) to a segment:offset address too. 
    Note that much like in farpeek, this version of farpoke saves and 
    restore the segment register used for the access.
*/

void farpokeb(word sel, void *off, byte v)
{
  asm("push %%fs; mov %0,%%fs;"
      "movb %2,%%fs:(%1);"
      "pop %%fs": :"g"(sel),"r"(off),"r"(v));
}

/*
 * I/O access
 * outb
 * inb
 * io_wait_jmp
 * io_wait
 */

/* OUTx
    sends a byte (or word or dword) on a I/O location. 
    Traditionnal names are outb, outw and outl respectively. the "a" modifier 
    enforce value to be placed in eax register before the asm command is 
    issued and "Nd" allows for one-byte constant values to be assembled as 
    constants and use edx register for other cases.
*/

void outb(unsigned short port, unsigned char val)
{
   asm volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

/* INx
    receives a byte (or word or dword) from an I/O location. 
    Traditionnal names are inb, inw and inl respectively
*/

unsigned char inb(unsigned short port)
{
   unsigned char ret;
   asm volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

/* IO_WAIT
    Forces the CPU to wait for an I/O operation to complete. 
    only use this when there's nothing like a status register or an IRQ 
    to tell you the info has been received.
*/

void io_wait_jmp(void)
{
   asm volatile("jmp 1f;1:jmp 1f;1:");
}

/*
    alternatively, you may use another I/O cycle on an 'unused' port 
    (which has the nice property of being CPU-speed independent):
*/

void io_wait(void)
{
   asm volatile("outb %%al, $0x80" : : "a"(0));
   // port 0x80 is used for 'checkpoints' during POST.
   // linux kernel seems to think it's free for use :-/
}

/*
 * Interrupt-related functions
 * irqEnabled
 * irqUnlock
 * lidt
 */

/* Enabled?
   returns a 'true' boolean value if irq are enabled at the CPU
*/

int irqEnabled()
{
        int f;
        asm volatile ("pushf;popl %0":"=g" (f));
        return f & (1<<9);
}

/* Acknowledge
   sends the PIC chip (8259a) that we're ready for more interrupts. 
   As pics are cascaded for int 8-15, if no>=8, we will have to send a 
   'clearance code' for both master and slave PICs.
*/

void irqUnlock(int no)
{
  /*             Val, Port */
  if (no>7) outb(0x20,0xa0);
  outb(0x20,0x20);
}

/* LIDT
   define a new interrupt table
*/

void lidt(void *base, unsigned int size) 
{
   unsigned int i[2];

   i[0] = size << 16;
   i[1] = (unsigned int) base;
   asm ("lidt (%0)": :"p" (((char *) i)+2));
}

/*
    The 'char* +2' trick avoids you to wonder whether the structure 
    packing/padding will work or not for that weird 6-bytes IDTR stuff.
*/

/* 
 * Cpu-related functions
 * cpuid
 * rdtsc
 * 
 */

/* CPUID
   request for CPU identification. See the CPUID page for more code snippets.
   Issue a single request to CPUID. Fits 'intel features', for instance.
*/

void cpuid(int code, dword *a, dword *d) 
{
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"0"(code));
}

/* RDTSC
   read the current value of the CPU's time-stamp counter and store 
   into EDX:EAX. The time-stamp counter contains the amount of clock ticks
   that have elapsed since the last CPU reset. 
   The value is stored in a 64-bit MSR and it increments after each clock cycle.

   This can be used to find out how much time it takes to do certain functions. 
   It's very useful for testing/benchmarking/etc. Note: This is only an
   approximation.
*/

void rdtsc(dword *upper, dword *lower)
{
  asm volatile("rdtsc\n" : "=a"(*lower), "=d"(*upper));
}

/* READ_CRx
   read the value in a control register
*/

unsigned read_cr0() 
{
   unsigned val;
   asm volatile("mov %%cr0, %0":"=r"(val));
   return val;
}

/* PGFLUSHTLB
    invalidates the TLB (Translation Lookaside Buffer) for one specific 
    virtual address (next memory reference for the page will be forced to 
    re-read PDE and PTE from main memory. Must be issued every time you
    update one of those tables). 
    m points to a logical address, not a physical or virtual one: an offset 
    for your ds segment. 

    Note *m is used, not just m: if you use m here, you invalidate 
    the address of the m variable (not what you want!).
*/

/* Not compiling with g++ 4.0.3
void pgFlushOneTlb(void *m)
{
  asm volatile("invlpg %0"::"m" (*m));
}
*/
