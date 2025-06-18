#include "nvic.h"

void NVIC_ConfigPriorities(void) {
    NVIC_SetPriority(EXTI0_IRQn, NVIC_PRIORITY_EXTI0);
    NVIC_SetPriority(EXTI1_IRQn, NVIC_PRIORITY_EXTI1);
    NVIC_SetPriority(TIM2_IRQn,  NVIC_PRIORITY_TIMER2);
    NVIC_SetPriority(SysTick_IRQn, NVIC_PRIORITY_SYSTICK);

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
}