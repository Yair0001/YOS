#include "pic.h"
#include "common/port.h"

void initPIC(){
    outb(MASTER_PIC_CMD_PORT, ICW1);
    ioWait();
    outb(SLAVE_PIC_CMD_PORT, ICW1);
    ioWait();

    outb(MASTER_PIC_DATA_PORT, MASTER_ICW2);
    ioWait();
    outb(SLAVE_PIC_DATA_PORT, SLAVE_ICW2);
    ioWait();

    outb(MASTER_PIC_DATA_PORT, MASTER_ICW3);
    ioWait();
    outb(SLAVE_PIC_DATA_PORT, SLAVE_ICW3);
    ioWait();

    outb(MASTER_PIC_DATA_PORT, ICW4);
    ioWait();
    outb(SLAVE_PIC_DATA_PORT, ICW4);
    ioWait();


    irqEnable(PIT_TIMER);
    irqEnable(KEYBOARD);
    irqEnable(SLAVE_PIC);
    irqEnable(RTC);
    irqEnable(MOUSE);
}

void irqDisable(uint8_t irq){
    if (irq > IRQ_NUM) return;

    uint16_t port;
    uint8_t val;

    if (irq < 8){
        port = MASTER_PIC_DATA_PORT;
    } else {
        port = SLAVE_PIC_DATA_PORT;
        irq -= 8;
    }

    val = inb(port) | (1 << irq);
    outb(port, val);
}

void irqEnable(uint8_t irq){
    if (irq > IRQ_NUM) return;

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = MASTER_PIC_DATA_PORT;
    } else {
        port = SLAVE_PIC_DATA_PORT;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}

void sendEOI(uint8_t irq){
    if (irq >= 8) outb(SLAVE_PIC_CMD_PORT, OCW2);
    outb(MASTER_PIC_CMD_PORT, OCW2);
}

uint16_t getIRR(){
    outb(MASTER_PIC_CMD_PORT, OCW3_IRR);
    outb(SLAVE_PIC_CMD_PORT, OCW3_IRR);
    return (inb(SLAVE_PIC_CMD_PORT) << 8) | inb(MASTER_PIC_CMD_PORT);
}

uint16_t getISR(){
    outb(MASTER_PIC_CMD_PORT, OCW3_ISR);
    outb(SLAVE_PIC_CMD_PORT, OCW3_ISR);
    return (inb(SLAVE_PIC_CMD_PORT) << 8) | inb(MASTER_PIC_CMD_PORT);
}