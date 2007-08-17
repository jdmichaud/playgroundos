# Makefile for Other kernel

ASM	= loader2.s init.s isr_wrapper.s
AOBJ	= $(addsuffix .o, $(basename $(ASM)))
SRC	= kernel.c asm.c remap_pic.c interrupt_handler.c console.c libc.c
OBJ	= $(addsuffix .o, $(basename $(SRC)))
CC 	= g++
CFLAGS 	= -Wall 		\
	  -nostdlib		\
	  -nostartfiles		\
	  -nodefaultlibs	\
	  -fno-rtti		\
	  -fno-exceptions
ASSBLER	= nasm
SFLAGS	= -f elf
ELF	= a.out


all: $(ELF) install

a.out: $(AOBJ) $(OBJ)
	ld --script linker.ld $(AOBJ) $(OBJ)

.s.o:
	$(ASSBLER) $(SFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c $<

install: $(ELF)
	cp $(ELF) ../iso/

clean:
	rm -fr *~
	rm -fr *.o
	rm -fr a.out

re: clean all

iso: all
	cd .. && ./mkiso.sh
