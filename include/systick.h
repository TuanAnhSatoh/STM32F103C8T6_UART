#ifndef SYSTICK_H
#define SYSTICK_H

#include <stm32f103xe.h>

void SysTick_Init(uint32_t tick_us);

#endif // SYSTICK_H