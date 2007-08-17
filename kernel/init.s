# init.s

global __installGDT
global __installIDT

extern gdtTablePointer_g
__installGDT:
	lgdt [gdtTablePointer_g]  ; Loads the GDT defined by the pointer
	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:__returnGDT ; 0x08 is the offset to our code segment: Far jump!
__returnGDT:
	ret

extern idtTablePointer_g
__installIDT:
	lidt [idtTablePointer_g]
	ret
	