#include "main.h"
#include "common/stdio.h"
#include "interrupts/idt.h"

void kern_main(){
    clearScreen();

    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");

    initIDT();

    printk("System ready.\n");

    while(1);
}

