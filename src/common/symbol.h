#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

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


void handleSignedIntSym(const char *modifiers, va_list *args);
void handleUnsignedIntSym(const char *modifiers, va_list *args);
void handleStringSym(const char *modifiers, va_list *args);
void handleCharSym(const char *modifiers, va_list *args);
void handleUnsignedHexSym(const char *modifiers, va_list *args);
void handlePointerSym(const char *modifiers, va_list *args);

HandlerFunc getHandler(Symbol type);

void parseSym(const char *str, va_list *args);
FullSymbol getSym(const char *str);
