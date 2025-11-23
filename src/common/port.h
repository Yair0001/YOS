#pragma once
#include <stdint.h>

#define DELAY_PORT 0x80

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void ioWait();