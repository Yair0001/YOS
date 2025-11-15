#pragma once
#include <stdint.h>
#include "../../common/printk.h"
#include "../../common/types.h"

#define X(n) extern void isr##n();
#define ISR_NUMBERS               \
    X(0)  X(1)  X(2)  X(3)  X(4)  \
    X(5)  X(6)  X(7)  X(8)  X(9)  \
    X(10) X(11) X(12) X(13) X(14) \
    X(16) X(17) X(18) X(19) X(20) \
    X(21)                         \
    X(22) X(23) X(24) X(25) X(26) \
    X(27) X(28) X(29) X(30) X(31) \
    X(32)

ISR_NUMBERS
#undef X


typedef struct __attribute__((packed)) {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers;

void isrHandler(registers* regs);

void divideErrorHandler(registers* regs);
