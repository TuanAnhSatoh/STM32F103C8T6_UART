#include "timer.h"

static void (*TIM3_Callback)(void) = 0;

void TIM2_Init(uint32_t freq) {
    // Bật clock cho TIM2
    Enable_TIMER_Clock(TIM2);

    uint32_t pclk1 = 36000000;
    uint32_t prescaler = (pclk1 / freq) - 1;

    TIM2->PSC = prescaler;      // Prescaler
    TIM2->ARR = 0xFFFFFFFF;     // Đếm tối đa
    TIM2->CNT = 0;              // Reset counter

    TIM2->CR1 |= TIM_CR1_CEN;   // Bật timer
}

uint32_t TIM2_GetCounter(void) {
    return TIM2->CNT;
}

void TIM2_Reset(void) {
    TIM2->CNT = 0;
}

// --- TIM3 functions for LED_Toggle ---

void TIM3_Init(uint32_t freq) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    uint32_t prescaler = 36000 - 1; // 36MHz / 3600 = 10kHz
    TIM3->PSC = prescaler;
    TIM3->ARR = (1000 / freq) - 1; // freq Hz
    TIM3->CNT = 0;

    TIM3->DIER |= TIM_DIER_UIE; // Cho phép ngắt tràn
    TIM3->CR1 |= TIM_CR1_URS;   // Chỉ tràn mới tạo ngắt
    NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_Start(void) {
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_Stop(void) {
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void TIM3_SetCallback(void (*callback)(void)) {
    TIM3_Callback = callback;
}

uint32_t TIM3_GetCounter(void) {
    return TIM3->CNT;
}

void TIM3_Reset(void) {
    TIM3->CNT = 0;
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR &= ~TIM_SR_UIF; // Xóa cờ ngắt
        if (TIM3_Callback) {
            TIM3_Callback();
        }
    }
}