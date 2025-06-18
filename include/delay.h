#ifndef DELAY_H
#define DELAY_H

#include <systick.h>

void SysTick_Handler(void);
void delay_ms(uint32_t ms);

#endif // DELAY_H