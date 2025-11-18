#include "main.h"
#include "../common/io.h"

void kern_main(){
    clear_screen();

    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");
    printk("System ready.\n");

    while(1);
}

