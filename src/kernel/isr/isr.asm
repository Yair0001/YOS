section .text

extern isrHandler

; Macro for ISRs that don't push an error code
%macro ISR_NO_ERR 1
global isr%1
isr%1:
    cli
    push 0          ; Push dummy error code
    push %1         ; Push interrupt number
    jmp isr_common
%endmacro

; Macro for ISRs that push an error code
%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    ; CPU already pushed error code
    push %1         ; Push interrupt number
    jmp isr_common
%endmacro

; CPU Exception ISRs (0-31)
ISR_NO_ERR 0    ; Divide by zero

; Common ISR handler
isr_common:
    ; Save all general purpose registers
    pushad

    ; Save segment registers
    push ds
    push es
    push fs
    push gs

    ; Load kernel data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Push pointer to register structure as parameter
    mov eax, esp
    push eax

    ; Call C handler
    call isrHandler

    ; Remove the parameter from stack
    add esp, 4

    ; Restore segment registers
    pop gs
    pop fs
    pop es
    pop ds

    ; Restore general purpose registers
    popad

    ; Clean up pushed error code and interrupt number
    add esp, 8

    ; Return from interrupt
    sti
    iret
