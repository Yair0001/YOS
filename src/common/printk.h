#pragma once

#include <stdarg.h>
#include <stdint.h>
#include "symbol.h"

#define VGA_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define MAX_OFFSET (VGA_WIDTH * VGA_HEIGHT)

typedef enum VGA_COLOR {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    BROWN,
    GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_PURPLE,
    YELLOW,
    WHITE
} VGA_COLOR;

struct Screen{
    volatile char* screen;
    uint32_t       offset;
};

void printk(const char *, ...);
void chrToScreen(char chr, VGA_COLOR color);
void updateOffset();