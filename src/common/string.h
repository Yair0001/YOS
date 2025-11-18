#pragma once

#include <stddef.h>
#include <stdbool.h>

#define SIZE_MAX ((size_t)-1)

#define CHECK_NULL_PTR(ptr) do { \
   if ((ptr) == NULL) return NULL_PTR; \
} while(0)

#define CHECK_BUFFER_SIZE(size) do { \
   if ((size) == 0) return INVALID_PARAM; \
} while(0)

typedef enum {
   SUCCESS = 0,
   NULL_PTR = -1,
   BUFFER_TOO_SMALL = -2,
   INVALID_PARAM = -3
} string_result_t;

size_t strlen_s(const char *str);
string_result_t strncpy_s(char *dest, size_t dest_size, const char *src, size_t count);
string_result_t strncat_s(char *dest, size_t dest_size, const char *src, size_t count);
int strncmp_s(const char *str1, const char *str2, size_t count);

int memcmp_s(const void *ptr1, const void *ptr2, size_t count);
string_result_t memcpy_s(void *dest, size_t dest_size, const void *src, size_t count);
string_result_t memmove_s(void *dest, size_t dest_size, const void *src, size_t count);
string_result_t memset_s(void *ptr, size_t ptr_size, int value, size_t count);

