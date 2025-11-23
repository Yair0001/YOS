#pragma once
#include <stdint.h>

#define COUNTER0_PORT 0x40
#define CONTROL_WORD_PORT 0x43

#define INP_CLK_HZ 1193181
#define WANTED_CLK_FREQ 1000

#define ENABLE_MODE3 0x36 // binary counting + mode 3 + channel 0

void initTimer();
uint32_t getTick();
void sleep(uint32_t ms);