[bits 16]
[org 0x7c00]

STAGE2_ADDR equ 0x7E00

start:
    cli ; disable interrupts

    ; setup registers
    xor ax, ax       ; AX = 0
    mov ds, ax       ; DS = 0
    mov es, ax       ; ES = 0
    mov ss, ax       ; SS = 0
    mov sp, 0x7c00   ; stack pointer
    sti ; enable interrupts

load_stage2:
    mov bx, STAGE2_ADDR

    mov dh, 0x00
    mov dl, 0x80
    mov cl, 0x02
    mov ch, 0x00
    mov ah, 0x02
    mov al, 2
    int 0x13

    jc disk_read_error

    jmp STAGE2_ADDR

disk_read_error:
    hlt
    
times 510-($-$$) db 0
dw 0xaa55
