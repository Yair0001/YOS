#include "irq.h"
#include "idt.h"
#include "pic.h"

static irq_handler_t irq_handlers[IRQ_COUNT] = {0};

static void (*const irq_stubs[IRQ_COUNT])(void) = {
    irq0,  irq1,  irq2,  irq3,  irq4,  irq5,  irq6,  irq7,
    irq8,  irq9,  irq10, irq11, irq12, irq13, irq14, irq15
};

void initIRQ(uint16_t selector, idtAttr attr) {
    for (int i = 0; i < IRQ_COUNT; i++) {
        setGate(32 + i, (uint32_t)irq_stubs[i], selector, attr);
    }
}

void registerIrqHandler(uint8_t irq, irq_handler_t handler) {
    if (irq < IRQ_COUNT) {
        irq_handlers[irq] = handler;
    }
}

void irqHandler(irq_registers* regs) {
    uint8_t irq = regs->int_no - 32;

    if (irq_handlers[irq]) {
        irq_handlers[irq](regs);
    }

    sendEOI(irq);
}
