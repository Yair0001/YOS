#pragma once
#include <stdint.h>
#include "idt.h"

#define ISR_COUNT 32

#define ISR(n) extern void isr##n(void)

ISR(0);  ISR(1);  ISR(2);  ISR(3);
ISR(4);  ISR(5);  ISR(6);  ISR(7);
ISR(8);  ISR(9);  ISR(10); ISR(11);
ISR(12); ISR(13); ISR(14); ISR(15);
ISR(16); ISR(17); ISR(18); ISR(19);
ISR(20); ISR(21); ISR(22); ISR(23);
ISR(24); ISR(25); ISR(26); ISR(27);
ISR(28); ISR(29); ISR(30); ISR(31);

#undef ISR

typedef struct __attribute__((packed)) {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers;

typedef void (*isr_handler_t)(registers*);

void isrHandler(registers* regs);
void registerIsrHandler(uint8_t isr, isr_handler_t handler);
void initISR(int amount, uint16_t selector, idtAttr attr);
