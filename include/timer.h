#ifndef TIMER_H
#define TIMER_H

#include <stm32f103xe.h>
#include <stdint.h>
#include <rcc.h>
#include <pinmap.h>
#include <gpio.h>
#include <led.h>

typedef void (*TimerCallback_t)(void);

void TIM2_Init(uint32_t freq);
void TIM2_Reset(void);
void TIM2_SetCallback(TimerCallback_t cb);
void TIM2_Stop(void);
void TIM2_IRQHandler(void);

#endif // TIMER_H