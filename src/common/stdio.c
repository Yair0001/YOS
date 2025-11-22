#include <stdint.h>
#include "stdio.h"
#include "intconv.h"

static struct Screen vgaScreen = {
    .pixels = (volatile struct PixelVGA*)VGA_ADDR,
    .offset = 0
};

static void scrollScreen(void) {
    for (uint32_t i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        vgaScreen.pixels[i] = vgaScreen.pixels[i + VGA_WIDTH];
    }

    for (uint32_t i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < MAX_OFFSET; i++) {
        vgaScreen.pixels[i].ch = ' ';
        vgaScreen.pixels[i].color = BLACK;
    }

    vgaScreen.offset = (VGA_HEIGHT - 1) * VGA_WIDTH;
}

void clearScreen(void) {
    for (uint32_t i = 0; i < MAX_OFFSET; i++) {
        vgaScreen.pixels[i].ch = ' ';
        vgaScreen.pixels[i].color = BLACK;
    }
    vgaScreen.offset = 0;
}

static void newLineToScreen(void) {
    uint32_t line = vgaScreen.offset / VGA_WIDTH;
    vgaScreen.offset = (line + 1) * VGA_WIDTH;
    if (vgaScreen.offset >= MAX_OFFSET)
        scrollScreen();
}

static void updateOffset(void) {
    vgaScreen.offset++;
    if (vgaScreen.offset >= MAX_OFFSET)
        scrollScreen();
}

void putc(char ch, VGA_COLOR color) {
    if (ch == NEW_LINE) {
        newLineToScreen();
        return;
    }

    vgaScreen.pixels[vgaScreen.offset].ch = ch;
    vgaScreen.pixels[vgaScreen.offset].color = color;
    updateOffset();
}

void puts(const char *str, VGA_COLOR color) {
    for (; *str != 0; str++) {
        putc(*str, color);
    }
}

static void handleSignedIntSym(const char *modifiers, va_list *args) {
    uint32_t n = va_arg(*args, uint32_t);
    char buf[32];
    const char *strNum = itoa(n, buf);
    puts(strNum, WHITE);
}

static void handleUnsignedIntSym(const char *modifiers, va_list *args) {
    uint32_t n = va_arg(*args, uint32_t);
    char buf[32];
    const char *strNum = utoa(n, buf);
    puts(strNum, WHITE);
}

static void handleUnsignedHexSym(const char *modifiers, va_list *args) {
    uint32_t n = va_arg(*args, uint32_t);
    char buf[32];
    const char *strNum = xtoa(n, buf);
    puts(strNum, WHITE);
}

static void handleStringSym(const char *modifiers, va_list *args) {
    const char *str = va_arg(*args, char*);
    puts(str, WHITE);
}

static void handleCharSym(const char *modifiers, va_list *args) {
    putc((char)va_arg(*args, int), WHITE);
}

static void handlePointerSym(const char *modifiers, va_list *args) {
    void* ptr = va_arg(*args, void*);
    uintptr_t addr = (uintptr_t)ptr;
    char buf[32];
    const char* strNum = xtoa(addr, buf);
    puts(strNum, WHITE);
}

static void defaultHandler(const char *str, va_list *args) {
    puts(str, WHITE);
}

static SymbolHandler symHandlers[] = {
    {SIGNED_INT, handleSignedIntSym},
    {UNSIGNED_INT, handleUnsignedIntSym},
    {STRING, handleStringSym},
    {CHAR, handleCharSym},
    {UNSIGNED_HEX, handleUnsignedHexSym},
    {POINTER, handlePointerSym},
};

static SymbolMap symMap = {
    symHandlers,
    sizeof(symHandlers) / sizeof(SymbolHandler)
};

static HandlerFunc getHandler(Symbol type) {
    for (uint32_t i = 0; i < symMap.count; i++) {
        if ((Symbol)symMap.map[i].sym == type) return symMap.map[i].handler;
    }
    return defaultHandler;
}

static FullSymbol getSym(const char *str) {
    static char modifiers[32];
    int mod_idx = 0;
    Symbol type = UNDEFINED;

    for (; *str != 0 && mod_idx < 31; str++) {
        Symbol current = (Symbol)*str;

        switch (current) {
            case SIGNED_INT:
            case UNSIGNED_INT:
            case STRING:
            case CHAR:
            case UNSIGNED_HEX:
            case POINTER:
                type = current;
                modifiers[mod_idx] = '\0';
                return (FullSymbol){type, modifiers};

            default:
                modifiers[mod_idx++] = *str;
                break;
        }
    }

    modifiers[mod_idx] = '\0';
    return (FullSymbol){type, modifiers};
}

static void parseSym(const char *str, va_list *args) {
    FullSymbol sym = getSym(str);
    getHandler(sym.type)(sym.modifiers, args);
}

void printk(const char *str, ...) {
    va_list args;
    va_start(args, str);

    for (; *str != 0; str++) {
        switch (*str) {
            case PERCENT_SIGN:
                str++;
                if (*str == 0) break;

                parseSym(str, &args);
                break;

            case NEW_LINE:
                newLineToScreen();
                break;

            default:
                putc(*str, WHITE);
                break;
        }
    }

    va_end(args);
}
