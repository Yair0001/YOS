#include "idt.h"

idtEntry idt[IDT_SIZE];
idtPtr idtr;
extern void (*isr_table[])();

void setGate(int num, uint32_t handler, uint16_t selector, idtAttr attr) {
    idt[num].offsetStart = handler & 0xFFFF;
    idt[num].segSelector = selector;
    idt[num].reserved    = 0;
    idt[num].attr        = attr;
    idt[num].offsetEnd   = (handler >> 16) & 0xFFFF;
}

void initISR(int amount, uint16_t selector, idtAttr attr){
    if (amount > 32) return;
    for(uint64_t i=0; i < amount; i++){
        if (isr_table[i] == NULL) continue;
        setGate(i, (uint32_t)isr_table[i], selector, attr);
    }
}

void initIDT() {
    for (int i = 0; i < IDT_SIZE; i++) {
        idt[i].offsetStart = 0;
        idt[i].segSelector = 0;
        idt[i].reserved    = 0;
        idt[i].attr.used   = 0;
        idt[i].offsetEnd   = 0;
    }

    idtAttr attr = {
        .gate       = INT32BIT,
        .reserved   = 0,
        .privileges = 0,
        .used       = 1
    };

    initISR(32,CODE_SEG_SELECTOR,attr);

    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)&idt;

    __asm__ volatile ("lidt %0" : : "m"(idtr));

    printk("IDT initialized with %d entries\n", IDT_SIZE);

}
