#include "timer.h"

static TimerCallback_t TIM2_Callback = 0;

void TIM2_Init(uint32_t freq) {
    Enable_TIMER_Clock(TIM2);

    TIM2_Reset();

    uint32_t prescaler = 72000 - 1; // tick mỗi 1ms
    TIM2->PSC = prescaler;
    TIM2->ARR = (1000 / freq) - 1; // freq = 1 → ARR = 999
    TIM2->CNT = 0;

    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_URS;
    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_Reset(void) {
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;  
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM2RST; 
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