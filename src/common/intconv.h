#pragma once

#include <stdint.h>

#define DECIMAL_BASE 10
#define HEX_BASE 16

// For now all of the functions here arent safe cause they dont check the size of buf, will be refactored in the future.

const char* itoa(int32_t n, char* buf);
const char* utoa(uint32_t n, char* buf);
const char* xtoa(uint32_t n, char* buf);