#include "symbol.h"
#include "../common/printk.h"

void handleSignedIntSym(const char *modifiers, va_list *args){

}
void handleUnsignedIntSym(const char *modifiers, va_list *args){

}
void handleStringSym(const char *modifiers, va_list *args){

}
void handleCharSym(const char *modifiers, va_list *args){

}
void handleUnsignedHexSym(const char *modifiers, va_list *args){

}
void handlePointerSym(const char *modifiers, va_list *args){

}

/*
    will just contain stuff after % that was invalid so i want to print as string.
*/
void defaultHandler(const char *str, va_list *args){
    handleStringSym(str, args);
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
    char* modifiers = "";
    Symbol type = UNDEFINED;
    for(; *str != 0; str++){
        switch ((Symbol) *str) {
            case SIGNED_INT:
                type = SIGNED_INT;
                break;
            case UNSIGNED_INT:
                type = UNSIGNED_INT;
                break;
            case STRING:
                type = STRING;
                break;
            case CHAR:
                type = CHAR;
                break;
            case UNSIGNED_HEX:
                type = UNSIGNED_HEX;
                break;
            case POINTER:
                type = POINTER;
                break;
            default:
                type = UNDEFINED;
        }
        if (type == UNDEFINED) modifiers += *str;
    }
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