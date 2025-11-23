#include "timer.h"
#include "irq.h"
#include "pic.h"
#include "common/port.h"
#include <stdint.h>

static volatile uint32_t tick = 0;
static void timerHandler(void* regs) {
    tick++;
}

static void initPIT(){
    uint16_t rate = INP_CLK_HZ / WANTED_CLK_FREQ;
    outb(CONTROL_WORD_PORT, ENABLE_MODE3);
    ioWait();
    outb(COUNTER0_PORT, rate & 0xFF); // LSB
    ioWait();
    outb(COUNTER0_PORT, rate >> 8); // MSB
}

void initTimer() {
    initPIT();
    irqEnable(PIT_TIMER);
    registerIrqHandler(PIT_TIMER, (irq_handler_t)timerHandler);
}

void sleep(uint32_t ms){
    // for now it will be busy loop until i will add threads and processes in the future

    uint32_t currTicks = getTick();
    while (getTick() < currTicks + ms);
}

uint32_t getTick(){
    return tick;
}