#include "main.h"

void kern_entry(){
    volatile char *screen = (volatile char*)0xB8000;
    *screen = 'd';
    *(screen+1) = 2;
    while(1);
}