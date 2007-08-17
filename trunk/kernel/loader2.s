[BITS 32]

SECTION .text
global _loader
_loader:
	mov esp, _systemStack ; This is a pointer to the system stack
	jmp start

align 4
	
_mboot:
; Multiboot macros to make a few lines later more readable
MULTIBOOT_PAGE_ALIGN   equ 1<<0
MULTIBOOT_MEMORY_INFO  equ 1<<1
MULTIBOOT_AOUT_KLUDGE  equ 1<<16
MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
MULTIBOOT_CHECKSUM  equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

extern code
extern bss
extern end

	; This is the GRUB Multiboot header. A boot signature
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM

    ; AOUT kludge - must be physical addresses. Make a note of these:
    ; The linker script fills in the data for these ones!
	dd _mboot
	dd _loader

start:
	;push dword 2 ; Prevents Task switching at IRET
	;popf

	push ebx
	push eax

	extern _main
    	call _main
	jmp $

section .bss
    resb 8192               ; This reserves 8KBytes of memory here
_systemStack:
