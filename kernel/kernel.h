#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "defines.h"

extern "C" void _main(void *mbd, unsigned int magic);
extern "C" void installGDT();
extern "C" void setGDTEntry(GDTEntry_s &entry, unsigned long address, 
			    unsigned long size, unsigned char type, 
			    unsigned char blockSize);
extern "C" void installIDT();
extern "C" void setIDTEntry(IDTEntry_s &entry, unsigned long address, 
			    unsigned long size, unsigned char type, 
			    unsigned char maxRingCallable);

extern "C" void __installGDT(void);
extern "C" void __installIDT(void);

#endif // ! _KERNEL_H_
