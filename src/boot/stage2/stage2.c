#include "stage2.h"
#include "../../common/printk.h"
#include "disk/disk.h"

void load_kern(){
    /*
        stuff need to do!
        load the kernel from address X (currently thinking about 2MB cause we loaded into PM so i can).
        jump to that address.

    disk_read
    // jump to that address
    */
    void (*kern_entry)(void) = (void*)0x100000;
    kern_entry();
}

void stage2_main(){
    printk("asdf\nadsf\nadsf\nasd");
    while(1);
}

