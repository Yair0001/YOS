#pragma once
#include <stdint.h>

#define MASTER_PIC_CMD_PORT 0x20
#define MASTER_PIC_DATA_PORT 0x21
#define SLAVE_PIC_CMD_PORT 0xA0
#define SLAVE_PIC_DATA_PORT 0xA1

#define ICW1 0x11 // IC4 enabled, SNGL disabled (2 PIC), LTIM disabled (using edge mode)
#define MASTER_ICW2 0x20 // Interrupt numbers start that will be in the idt (start from 32)
#define MASTER_ICW3 0x04 // Slave is sitting on IRQ 2 (bit mask: 00000100) (this is the common IRQ num i have seen)

#define SLAVE_ICW2 0x28 
#define SLAVE_ICW3 0x02 // Slave is on IRQ 2 of master PIC and here bits 2-0 is slave ID (010)

#define ICW4 0x01 // not using AUTOEOI, BUF=0, SFNM disabled (simpler and not needed for this OS)

#define OCW2 0x20 // using Non specific EOI
#define OCW3_IRR 0x0A // read IRR
#define OCW3_ISR 0x0B // read ISR

#define IRQ_NUM 15 // starts from 0

typedef enum {
    PIT_TIMER,
    KEYBOARD,
    SLAVE_PIC,
    COM2,
    COM1,
    LPT2,
    FLOPPY_DISK,
    LPT1,
    RTC,
    MOUSE = 12,
    FPU,
    ATA1,
    ATA2,
} IRQ;

void initPIC();
void irqEnable(uint8_t irq);
void irqDisable(uint8_t irq);
void sendEOI(uint8_t irq);
uint16_t getIRR();
uint16_t getISR();