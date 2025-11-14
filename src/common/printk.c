#include <stdint.h>
#include "printk.h"
#include "symbol.h"

static struct Screen vgaScreen = {
    .pixels = (volatile struct PixelVGA*)VGA_ADDR,
    .offset = 0
};

void newLineToScreen() {
    uint32_t line = vgaScreen.offset / VGA_WIDTH;
    vgaScreen.offset = (line + 1) * VGA_WIDTH;
    if (vgaScreen.offset >= MAX_OFFSET)
        vgaScreen.offset = 0;
}

void updateOffset() {
    vgaScreen.offset++;
    if (vgaScreen.offset >= MAX_OFFSET) vgaScreen.offset = 0;
}

void chrToScreen(char ch, VGA_COLOR color){
    if(ch == NEW_LINE){
        newLineToScreen();
        return;
    }

    vgaScreen.pixels[vgaScreen.offset].ch = ch;
    vgaScreen.pixels[vgaScreen.offset].color = color;
    updateOffset();
}

void strToScreen(const char *str, VGA_COLOR color){
    for(; *str != 0; str++){
        chrToScreen(*str, color);
    }
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
                newLineToScreen();
                break;
            default:
                chrToScreen(*str, WHITE);
        }
    }
    va_end(args);
}
