#ifndef NVIC_H
#define NVIC_H

#include <stm32f103xe.h>

#define NVIC_PRIORITY_EXTI0       0
#define NVIC_PRIORITY_EXTI1       1
#define NVIC_PRIORITY_TIMER2      2
#define NVIC_PRIORITY_UART1       3

void NVIC_ConfigPriorities(void);

#endif // NVIC_H