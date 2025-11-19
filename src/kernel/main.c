#include "main.h"
#include "../common/io.h"
#include "idt.h"

void kern_main(){
    clear_screen();

    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");

    initIDT();

    printk("System ready.\n");
    while(1);

#ifdef TEST_DIVIDE_BY_ZERO
    printk("Testing division ISR with divide-by-zero...\n");

    // Trigger divide-by-zero exception to test division ISR
    volatile int x = 1;
    volatile int y = 0;
    volatile int z = x / y;  // This should trigger ISR 0

    (void)z;  // Prevent unused variable warning
#endif

    
}

