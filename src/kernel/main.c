#include "main.h"
#include "../common/printk.h"
#include "idt.h"

// Uncomment to test divide-by-zero exception handler
// #define TEST_DIVIDE_BY_ZERO

void kern_main(){
    printk("Welcome to YOS!\n");
    printk("Kernel loaded at 0x7E00\n");

    // Initialize Interrupt Descriptor Table
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

