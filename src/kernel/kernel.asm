[bits 16]

section .text.boot

CODE_OFFSET equ 0x8
DATA_OFFSET equ 0x10

global _start
extern kern_main

_start:

load_PM:
    cli ; disable interrupts
    lgdt[gdt_descriptor]
    
    mov eax, cr0
    or al, 1
    mov cr0, eax

    ; enable A20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    jmp CODE_OFFSET:PModeMain

gdt_start:
null_desc:
    dd 0x0
    dd 0x0

code_desc:
    dw 0xFFFF ; limit
    dw 0x0000 ; base
    db 0x00 ; base
    db 10011010b ; access
    db 11001111b ; flags
    db 0x00 ; base

data_desc:
    dw 0xFFFF ; limit
    dw 0x0000 ; base
    db 0x00 ; base
    db 10010010b ; access
    db 11001111b ; flags
    db 0x00 ; base

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of gdt -1
    dd gdt_start

[bits 32]
PModeMain:
    mov ax, DATA_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ss, ax
    mov gs, ax
    mov ebp, 0x9c00
    mov esp, ebp

   jmp kern_main
