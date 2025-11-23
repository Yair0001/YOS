#include "main.h"
#include "common/stdio.h"
#include "interrupts/idt.h"
#include "interrupts/pic.h"
#include "interrupts/timer.h"

void kern_main(){
    clearScreen();

    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");

    initIDT();
    initPIC();
    initTimer();

    printk("System ready.\n");

    __asm__ volatile("sti");

    while(1);
}

