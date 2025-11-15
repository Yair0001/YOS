[bits 16]
[org 0x7c00]

KERN_ADDR equ 0x7E00

start:
    cli ; disable interrupts

    ; setup registers
    xor ax, ax       ; AX = 0
    mov ds, ax       ; DS = 0
    mov es, ax       ; ES = 0
    mov ss, ax       ; SS = 0
    mov sp, 0x7c00   ; stack pointer
    sti ; enable interrupts

load_kernel:
    mov bx, KERN_ADDR

    mov dh, 0x00      ; Head 0
    mov dl, 0x80      ; Drive 0x80 (first hard disk)
    mov cl, 0x02      ; Sector 2 (kernel starts after MBR)
    mov ch, 0x00      ; Cylinder 0
    mov ah, 0x02      ; BIOS read sectors function
%ifdef KERNEL_SECTORS
    mov al, KERNEL_SECTORS  ; Number of sectors to read (calculated by Makefile)
%else
    mov al, 64        ; Fallback: Load up to 64 sectors if not defined
%endif
    int 0x13

    jc disk_read_error

    jmp KERN_ADDR

disk_read_error:
    hlt
    
times 510-($-$$) db 0
dw 0xaa55
