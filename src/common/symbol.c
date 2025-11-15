#include "symbol.h"
#include "../common/intconv.h"
#include "../common/printk.h"
#include <stdint.h>

void handleSignedIntSym(const char *modifiers, va_list *args){
    uint32_t n = va_arg(*args,uint32_t);
    char buf[32];
    const char *strNum = itoa(n, buf);
    strToScreen(strNum, WHITE);
}

/*
    @param: modifiers - will be a string of modifiers and u at the end (ex. 05u for %05u)
    @param: args - contains all arguments after str in printk

    (for now only expect for %u, not handling for %05u or else)
*/
void handleUnsignedIntSym(const char *modifiers, va_list *args){
    uint32_t n = va_arg(*args,uint32_t);
    char buf[32];
    const char *strNum = utoa(n, buf);
    strToScreen(strNum, WHITE);
}

void handleUnsignedHexSym(const char *modifiers, va_list *args){
    uint32_t n = va_arg(*args,uint32_t);
    char buf[32];
    const char *strNum = xtoa(n, buf);
    strToScreen(strNum, WHITE);
}

/*
    @param: modifiers - will be a string of modifiers and s at the end (ex. 05s for %05s)
    @param: args - contains all arguments after str in printk

    (for now only expect for %s, not handling for %05s or else)
*/
void handleStringSym(const char *modifiers, va_list *args){
    const char *str = va_arg(*args, char*);
    strToScreen(str, WHITE);
}

/*
    @param: modifiers - will be a string of modifiers and c at the end (ex. 05c for %05c)
    @param: args - contains all arguments after str in printk

    (for now only expect for %c, not handling for %05c or else)
*/
void handleCharSym(const char *modifiers, va_list *args){
    chrToScreen((char)va_arg(*args, int), WHITE);
}

void handlePointerSym(const char *modifiers, va_list *args) {
    void* ptr = va_arg(*args, void*);
    uintptr_t addr = (uintptr_t)ptr;
    char buf[32];
    const char* strNum = xtoa(addr, buf);
    strToScreen(strNum, WHITE);
}

/*
    will just contain stuff after % that was invalid so i want to print as string.
*/
void defaultHandler(const char *str, va_list *args){
    strToScreen(str, WHITE);
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


FullSymbol getSym(const char *str){
    static char modifiers[32];
    int mod_idx = 0;
    Symbol type = UNDEFINED;
    
    for(; *str != 0 && mod_idx < 31; str++){
        Symbol current = (Symbol) *str;
        
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

void parseSym(const char *str, va_list *args){
    FullSymbol sym = getSym(str);
    getHandler(sym.type)(sym.modifiers, args);
}

HandlerFunc getHandler(Symbol type){
    for(uint32_t i=0; i < symMap.count; i++){
        if ((Symbol)symMap.map[i].sym == type) return symMap.map[i].handler;
    }
    return defaultHandler;
}