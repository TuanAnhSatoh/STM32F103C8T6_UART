#include "delay.h"

void delay_us(uint32_t us) {
    TIM2_Init(1000000);
    TIM2_Reset();
    while (TIM2_GetCounter() < us);
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        delay_us(1000);
    }
}