#ifndef TIMER_H
#define TIMER_H

#include <stm32f103xe.h>
#include <stdint.h>
#include <rcc.h>
#include <pinmap.h>
#include <gpio.h>


void TIM2_Init(uint32_t freq);
uint32_t TIM2_GetCounter(void);
void TIM2_Reset(void);

void TIM3_Init(uint32_t freq);
void TIM3_Start(void);
void TIM3_Stop(void);
void TIM3_SetCallback(void (*callback)(void));
uint32_t TIM3_GetCounter(void);
void TIM3_Reset(void);

#endif // TIMER_H