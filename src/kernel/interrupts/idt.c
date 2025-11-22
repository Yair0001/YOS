#include "idt.h"

static idtEntry idt[IDT_SIZE];
static struct idtr idtr;

void setGate(int num, uint32_t handler, uint16_t selector, idtAttr attr) {
    idt[num].offsetStart = handler & 0xFFFF;
    idt[num].segSelector = selector;
    idt[num].reserved    = 0;
    idt[num].attr        = attr;
    idt[num].offsetEnd   = (handler >> 16) & 0xFFFF;
}

void initIDT() {
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)&idt;

    idtAttr attr = {
        .gate       = INT32BIT,
        .reserved   = 0,
        .privileges = 0,
        .used       = 1
    };

    initISR(ISR_COUNT, 0x08, attr);

    __asm__ volatile ("lidt %0" : : "m"(idtr));

    printk("IDT initialized with %d entries\n", IDT_SIZE);
}
