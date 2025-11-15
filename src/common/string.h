#pragma once
#include "types.h"
#include <stdbool.h>

typedef enum {
    EQUAL = 0,
    LESS  = -1,
    GREATER = 1
} cmpRes;

size_t strlen(const char *str);

char *strncat(char *dest, const char *src, size_t n);
char *strcat(char *str1, const char *str2);

char *strncpy(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);

cmpRes strncmp(const char *str1, const char *str2, size_t n);
cmpRes strcmp(const char *str1, const char *str2);

char *strtok(char *str, const char *delim);

cmpRes memcmp(const void *m1, const void *m2, size_t size);
void *memchr(const void *str, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *str, int c, size_t n);