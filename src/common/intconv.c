#include "intconv.h"

#include <stdint.h>

/**
 * @brief General number-to-string converter.
 *
 * @param num       The number to convert (unsigned).
 * @param buf       Buffer to write into.
 * @param base      Numeric base (10 for decimal, 16 for hex, etc.).
 * @param is_signed 1 if the original number is signed, and negative values should get a '-' prefix.
 * @return          Pointer to the buffer.
 */
 static const char* num_to_str(int64_t num, char* buf, int base, int is_signed) {
    static const char digits[] = "0123456789ABCDEF";
    char* ptr = buf;
    char* start;
    char tmp;
    uint32_t uval;

    if (is_signed && num < 0) {
        *ptr++ = '-';
        uval = (uint32_t)(-num);
    } else {
        uval = (uint32_t)num;
    }

    start = ptr;

    if (uval == 0) {
        *ptr++ = '0';
    } else {
        while (uval != 0) {
            *ptr++ = digits[uval % base];
            uval /= base;
        }
    }

    *ptr-- = '\0';

    while (start < ptr) {
        tmp = *ptr;
        *ptr-- = *start;
        *start++ = tmp;
    }

    return buf;
}

/**
 * @brief Convert an unsigned integer to a decimal string.
 *
 * @param num  The number to convert.
 * @param buf  The buffer to write into. Must be large enough.
 * @return     Pointer to the buffer.
 */
const char* utoa(uint32_t n, char* buf) {
    return num_to_str(n, buf, DECIMAL_BASE, 0);
}

/**
 * @brief Convert a signed integer to a decimal string.
 *
 * @param n    The number to convert.
 * @param buf  The buffer to write into. Must be large enough.
 * @return     Pointer to the buffer.
 */const char* itoa(int32_t n, char* buf) {
    return num_to_str(n, buf, DECIMAL_BASE, 1);
}

/**
 * @brief Convert an unsigned integer to a hexadecimal string.
 *
 * @param num  The number to convert.
 * @param buf  The buffer to write into. Must be large enough.
 * @return     Pointer to the buffer.
 */
 const char* xtoa(uint32_t n, char* buf) {
    return num_to_str(n, buf, HEX_BASE, 0);
}
