#include "defines.h"
#include "kernel.h"
#include "asm.h"
#include "remap_pic.h"
#include "console.h"
#include "libc.h"
#include "interrupt_handler.h"

GDTTablePtr_s gdtTablePointer_g;
GDTEntry_s    gdtTable_g[GDT_TABLE_SIZE];
IDTTablePtr_s idtTablePointer_g;
IDTEntry_s    idtTable_g[IDT_TABLE_SIZE];

void _main(void *mbd, unsigned int magic)
{
  // This is the kernel
  Console console;
  console.cls();

  console.print("Remapping PICs...\n");
  remap_pics(0x20, 0x28);
  console.print("PICs remapped\n");

  console.print("Installing GDT...\n");
  installGDT();
  console.print("GDT installed\n");

  console.print("Installing IDT...\n");
  installIDT();
  console.print("IDT installed\n");

  console.print("Installing ISR...\n");
  installISR();
  console.print("ISR installed\n");

  console.print("System will now halt. Please reboot.");
}

void installGDT()
{
  gdtTablePointer_g.size = (sizeof(GDTEntry_s) * GDT_TABLE_SIZE) - 1;
  gdtTablePointer_g.tableAddress = (unsigned int) &gdtTable_g;

  // The first GDT must be NULL
  setGDTEntry(gdtTable_g[0], 0, 0, 0, 0);

  // Selector 8 will be our code
  setGDTEntry(gdtTable_g[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);

  // Selector 0x10 will be our data
  setGDTEntry(gdtTable_g[2], 0, 0xFFFFFFFF, 0x92, 0xCF);

  __installGDT();
}

void setGDTEntry(GDTEntry_s &entry, unsigned long address, unsigned long size, 
		 unsigned char type, unsigned char blockSize)
{
  entry.addressLow = (address & 0xFFFF);
  entry.addressMiddle = (address >> 16) & 0xFF;
  entry.addressHigh = (address >> 24) & 0xFF;
  
  entry.sizeLow = (size & 0xFFFF);
  entry.blockSize = ((size >> 16) & 0x0F);
  
  entry.blockSize |= (blockSize & 0xF0);
  entry.type = type;
}

void installIDT()
{
  idtTablePointer_g.size = (sizeof(IDTEntry_s) * 256) - 1;
  idtTablePointer_g.tableAddress = (unsigned int) &idtTable_g;

  memset(&idtTable_g, 0, (sizeof(IDTEntry_s) * 256));
  __installIDT();
}

void setIDTEntry(IDTEntry_s &entry, unsigned long address, 
		 unsigned long segmentSelector, 
		 unsigned char type, unsigned char maxRingCallable)
{
  entry.addressLow = (address & 0xFFFF);
  entry.addressHigh = (address >> 16) & 0xFFFF;
  
  entry.segmentSelector = segmentSelector;
  entry.always0 = 0; // Always set this to 0
  
  entry.accessFlags = 14 + (maxRingCallable << 5) & 0x80;
}

void installISR()
{
  for (int i = 0; i < ISR_TABLE_SIZE; ++i)
  {
    setIDTEntry(idtTable_g[i], (unsigned) isrFunctionTable_g[i], 0x08, 0);
  }
}
