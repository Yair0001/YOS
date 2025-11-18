#include "string.h"



size_t strlen_s(const char *str) {
    if (str == NULL) return 0;
    
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
        if (len > SIZE_MAX - 1) break;
    }
    return len;
}

string_result_t strncpy_s(char *dest, size_t dest_size, const char *src, size_t count) {
    CHECK_NULL_PTR(dest);
    CHECK_NULL_PTR(src);
    CHECK_BUFFER_SIZE(dest_size);
    
    if (count >= dest_size) {
        return BUFFER_TOO_SMALL;
    }
    
    size_t i;
    for (i = 0; i < count && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    
    dest[i] = '\0';
    
    return SUCCESS;
}

string_result_t strncat_s(char *dest, size_t dest_size, const char *src, size_t count) {
    CHECK_NULL_PTR(dest);
    CHECK_NULL_PTR(src);
    CHECK_BUFFER_SIZE(dest_size);
    
    size_t dest_len = 0;
    while (dest_len < dest_size && dest[dest_len] != '\0') {
        dest_len++;
    }
    
    if (dest_len == dest_size) {
        return INVALID_PARAM;
    }
    
    size_t available = dest_size - dest_len - 1;
    size_t copy_len = (count < available) ? count : available;
    
    size_t i;
    for (i = 0; i < copy_len && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    
    dest[dest_len + i] = '\0';
    return SUCCESS;
}

int strncmp_s(const char *str1, const char *str2, size_t count) {
    if (count == 0) return 0;
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    if (str2 == NULL) return 1;
    
    while (count > 0 && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        count--;
    }
    
    if (count == 0) return 0;
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int memcmp_s(const void *ptr1, const void *ptr2, size_t count) {
    if (ptr1 == ptr2) return 0;
    if (ptr1 == NULL) return -1;
    if (ptr2 == NULL) return 1;
    
    const unsigned char *p1 = (const unsigned char*)ptr1;
    const unsigned char *p2 = (const unsigned char*)ptr2;
    
    for (size_t i = 0; i < count; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    
    return 0;
}

string_result_t memcpy_s(void *dest, size_t dest_size, const void *src, size_t count) {
    CHECK_NULL_PTR(dest);
    CHECK_NULL_PTR(src);
    
    if (count > dest_size) {
        return BUFFER_TOO_SMALL;
    }
    
    const unsigned char *src_ptr = (const unsigned char*)src;
    unsigned char *dest_ptr = (unsigned char*)dest;
    
    if ((src_ptr >= dest_ptr && src_ptr < dest_ptr + count) ||
        (dest_ptr >= src_ptr && dest_ptr < src_ptr + count)) {
        return INVALID_PARAM;
    }
    
    for (size_t i = 0; i < count; i++) {
        dest_ptr[i] = src_ptr[i];
    }
    
    return SUCCESS;
}

string_result_t memmove_s(void *dest, size_t dest_size, const void *src, size_t count) {
    CHECK_NULL_PTR(dest);
    CHECK_NULL_PTR(src);
    
    if (count > dest_size) {
        return BUFFER_TOO_SMALL;
    }
    
    const unsigned char *src_ptr = (const unsigned char*)src;
    unsigned char *dest_ptr = (unsigned char*)dest;
    
    if (dest_ptr <= src_ptr || dest_ptr >= src_ptr + count) {
        for (size_t i = 0; i < count; i++) {
            dest_ptr[i] = src_ptr[i];
        }
    } else {
        for (size_t i = count; i > 0; i--) {
            dest_ptr[i - 1] = src_ptr[i - 1];
        }
    }
    
    return SUCCESS;
}

string_result_t memset_s(void *ptr, size_t ptr_size, int value, size_t count) {
    CHECK_NULL_PTR(ptr);
    
    if (count > ptr_size) {
        return BUFFER_TOO_SMALL;
    }
    
    unsigned char *p = (unsigned char*)ptr;
    unsigned char val = (unsigned char)value;
    
    for (size_t i = 0; i < count; i++) {
        p[i] = val;
    }
    
    return SUCCESS;
}