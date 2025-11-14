#include "stage2.h"
#include "../../common/printk.h"

void stage2_main(){
    printk("%u", -123);
    while(1);
}