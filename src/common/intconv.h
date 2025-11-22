#pragma once

#include <stdint.h>

#define DECIMAL_BASE 10
#define HEX_BASE 16

const char* itoa(int32_t n, char* buf);
const char* utoa(uint32_t n, char* buf);
const char* xtoa(uint32_t n, char* buf);