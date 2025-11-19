#pragma once
#include <stdint.h>

#include "isr/isr.h"
#include "../common/io.h"
#include "../common/types.h"


#define IDT_SIZE 256
#define CODE_SEG_SELECTOR 0x10

typedef enum : uint8_t {
    TASK      = 0x5,
    INT16BIT  = 0x6,
    TRAP16BIT = 0x7,
    INT32BIT  = 0xE,
    TRAP32BIT = 0xF
} gateType;

typedef struct __attribute__((packed)) {
    gateType gate       : 4;
    uint8_t reserved    : 1;
    uint8_t privileges  : 2;
    uint8_t used        : 1;
} idtAttr;

typedef struct __attribute__((packed)) {
    uint16_t offsetStart;    // low 16 bits of handler
    uint16_t segSelector;    // code segment selector
    uint8_t reserved;        // always zero
    idtAttr attr;            // type + privilege
    uint16_t offsetEnd;      // high 16 bits of handler
} idtEntry;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base;
} idtPtr;

void initIDT();
void setGate(int num, uint32_t handler, uint16_t selector, idtAttr attr);
void initISR(int amount, uint16_t selector, idtAttr attr);