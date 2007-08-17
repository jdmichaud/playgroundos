#ifndef _DEFINES_H_
#define _DEFINES_H_

#define GDT_TABLE_SIZE 17
#define IDT_TABLE_SIZE 256
#define ISR_TABLE_SIZE 32

char *gdt_labels_g[GDT_TABLE_SIZE] = 
{
  "Divide Error",
  "Debug Exceptions",
  "Reserved",
  "Breakpoint",
  "Overflow",
  "Bounds Check",
  "Invalid Opcode",
  "Coprocessor Not Available",
  "Double Fault",
  "Coprocessor Segment Overrun",
  "Invalid TSS",
  "Segment Not Present",
  "Stack Exception",
  "General Protection Exception (Triple Fault)",
  "Page Fault",
  "Reserved",
  "Coprocessor Error"
};

struct GDTEntry_s
{
    unsigned short sizeLow;
    unsigned short addressLow;
    unsigned char  addressMiddle;
    unsigned char  type;
    unsigned char  blockSize;
    unsigned char  addressHigh;
} __attribute__((packed));

struct GDTTablePtr_s
{
    unsigned short size;
    unsigned int   tableAddress;
} __attribute__((packed));

struct IDTEntry_s
{
    unsigned short addressLow;
    unsigned short segmentSelector;        /* Our kernel segment goes here! */
    unsigned char  always0;     /* This will ALWAYS be set to 0! */
    unsigned char  accessFlags;
    unsigned short addressHigh;
} __attribute__((packed));

struct IDTTablePtr_s
{
    unsigned short size;
    unsigned int   tableAddress;
} __attribute__((packed));

typedef extern "C" void (*) (void) ISRFunction_t;

#endif // ! _DEFINES_H_
