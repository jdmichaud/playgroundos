#ifndef _ASM_H_
#define _ASM_H_

#include "types.h"

// Memory access
extern "C" dword    farpeekl(word sel,void *off);
extern "C" void     farpokeb(word sel, void *off, byte v);

// I/O access
extern "C" void     outb(unsigned short port, unsigned char val);
extern "C" unsigned char inb(unsigned short port);
extern "C" void     io_wait_jmp(void);
extern "C" void     io_wait(void);

// Interrupt-related functions
extern "C" int      irqEnabled();
extern "C" void     irqUnlock(int no);
extern "C" void     lidt(void *base, unsigned int size);

// Cpu-related functions
extern "C" void     cpuid(int code, dword *a, dword *d) ;
extern "C" void     rdtsc(dword *upper, dword *lower);
extern "C" unsigned read_cr0() ;

//void     pgFlushOneTlb(void *m);

#endif // ! _ASM_H_
