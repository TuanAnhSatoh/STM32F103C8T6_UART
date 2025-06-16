#ifndef SWITCH_H
#define SWITCH_H

#include <stm32f103xe.h>
#include <gpio.h>
#include <rcc.h>
#include <pinmap.h>

void Switch_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

#endif // SWITCH_H