#include "timer.h"

static TimerCallback_t TIM2_Callback = 0;

void TIM2_Init(uint32_t freq) {
    Enable_TIMER_Clock(TIM2);

    uint32_t prescaler = 72000 - 1; 
    TIM2->PSC = prescaler;
    TIM2->ARR = (1000 / freq) - 1; 
    TIM2->CNT = 0;

    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_URS;

    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn,  2);
}

void TIM2_SetCallback(TimerCallback_t cb) {
    TIM2_Callback = cb;
}

void TIM2_Stop(void) {
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->DIER &= ~TIM_DIER_UIE;
    NVIC_DisableIRQ(TIM2_IRQn);
    TIM2_Callback = 0;
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        if (TIM2_Callback) {
            TIM2_Callback();
        }
    }
}