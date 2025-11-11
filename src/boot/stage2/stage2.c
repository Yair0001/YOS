#include "stage2.h"
#include "disk.h"

void load_kern(){
    /*
        stuff need to do!
        load the kernel from address X (currently thinking about 2MB cause we loaded into PM so i can).
        jump to that address.

    disk_read
    // jump to that address
    void (*kern_entry)(void) = (void*)0x200000;
    kern_entry();
    */
}

void stage2_main(){
    // test
    volatile char *screen = (volatile char*)0xB8000;
    *screen = 'd';
    *(screen+1) = 2;
    while(1);

    load_kern();
}
