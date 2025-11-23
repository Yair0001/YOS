#include "main.h"
#include "common/stdio.h"
#include "interrupts/idt.h"
#include "interrupts/pic.h"
#include "interrupts/timer.h"
#include <stdint.h>

void kern_main(){
    clearScreen();

    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");

    initIDT();
    initPIC();

    printk("System ready.\n");

    __asm__ volatile("sti");

    uint32_t cnt = 1;
    while (1){
        sleep(1000);
        printk("Slept for %d seconds\n", cnt);
        cnt++;
    }

    while(1);
}

