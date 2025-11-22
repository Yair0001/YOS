#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define VGA_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define MAX_OFFSET (VGA_WIDTH * VGA_HEIGHT)

#define PERCENT_SIGN '%'
#define NEW_LINE '\n'

typedef enum VGA_COLOR : uint8_t {
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

struct PixelVGA{
    char ch;
    VGA_COLOR color;
};

struct Screen{
    volatile struct PixelVGA *pixels;
    uint32_t                  offset;
};

typedef void (*HandlerFunc)(const char*, va_list*);

typedef enum {
    SIGNED_INT = 'd',
    UNSIGNED_INT = 'u',
    STRING = 's',
    CHAR = 'c',
    UNSIGNED_HEX = 'x',
    POINTER = 'p',
    UNDEFINED
} Symbol;

typedef struct {
    Symbol type;
    char *modifiers;
} FullSymbol;

typedef struct {
    Symbol sym;
    HandlerFunc handler;
} SymbolHandler;

typedef struct {
    SymbolHandler *map;
    uint32_t count;
} SymbolMap;

void clearScreen(void);
void printk(const char *, ...);
void putc(char chr, VGA_COLOR color);
void puts(const char *str, VGA_COLOR color);
