#include <stdint.h>
#include "printk.h"
#include "symbol.h"

struct Screen vgaScreen = {
    .screen = (volatile char*)VGA_ADDR,
    .offset = 0
};

void updateOffset(){
    if (vgaScreen.offset == MAX_OFFSET) vgaScreen.offset = 0;
    vgaScreen.offset++;
}

void chrToScreen(char chr, VGA_COLOR color){
    *vgaScreen.screen++ = chr;
    *vgaScreen.screen++ = color;
    updateOffset();
}

void printk(const char *str, ...){
    va_list args;
    va_start(args, str);
    
    for(; *str != 0; str++){
        switch (*str) {
            case PERCENT_SIGN:
                parseSym(str++, &args);
                break;
            case NEW_LINE:
                
            default:
                chrToScreen(*str, WHITE);
        }
    }
}
