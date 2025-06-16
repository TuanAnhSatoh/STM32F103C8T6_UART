#include "delay.h"

static volatile uint32_t ms_count = 0;

// Hàm này sẽ được gọi trong SysTick_Handler
void SysTick_Handler(void) {
    ms_count++;
}

void delay_ms(uint32_t ms) {
    uint32_t start = ms_count;
    while ((ms_count - start) < ms);
}