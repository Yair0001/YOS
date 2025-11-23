#pragma once
#include <stdint.h>
#include "idt.h"
#include "isr.h"

#define IRQ_COUNT 16

#define IRQ(n) extern void irq##n(void)

IRQ(0);  IRQ(1);  IRQ(2);  IRQ(3);
IRQ(4);  IRQ(5);  IRQ(6);  IRQ(7);
IRQ(8);  IRQ(9);  IRQ(10); IRQ(11);
IRQ(12); IRQ(13); IRQ(14); IRQ(15);

#undef IRQ

typedef void (*irq_handler_t)(registers*);

void irqHandler(registers* regs);
void registerIrqHandler(uint8_t irq, irq_handler_t handler);
void initIRQ(uint16_t selector, idtAttr attr);
