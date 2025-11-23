#include "timer.h"
#include "irq.h"
#include "common/stdio.h"
#include "pic.h"

void timerHandler(void* regs) {
    printk(".");
}

void initTimer() {
    registerIrqHandler(PIT_TIMER, (irq_handler_t)timerHandler);
}
