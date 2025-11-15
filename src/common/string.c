#include "string.h"
#include <stdint.h>


size_t strlen(const char *s){
    size_t len = 0;
    while(*s++ != 0) len++;
    return len;
}


cmpRes strncmp(const char *s1, const char *s2, size_t n) {
    size_t c = 0;

    while (c < n && *s1 && *s2 && ((unsigned char)*s1 == (unsigned char)*s2)) {
        s1++;
        s2++;
        c++;
    }

    if (c == n) return EQUAL;

    unsigned char us1 = (unsigned char)*s1;
    unsigned char us2 = (unsigned char)*s2;

    if (us1 == us2) return EQUAL;
    else if (us1 < us2) return LESS;
    return GREATER;
}

cmpRes strcmp(const char *s1, const char *s2) {
    cmpRes r = strncmp(s1, s2, strlen(s1));
    if (r == EQUAL) {
        if (*s2) return LESS;
        else return EQUAL;
    }
    return r;
}