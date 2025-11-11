#include "stage2.h"

void stage2_main(){
    volatile char *screen = (volatile char*)0xB8000;
    *screen = 'S';
    *(screen+1) = 1;
    while(1);
}