#include "delay.h"

static volatile uint32_t ms_count = 0;
static volatile uint32_t us_count = 0;

// Hàm này sẽ được gọi trong SysTick_Handler
void SysTick_Handler(void) {
    ms_count++;
    us_count += 1000;
}

void delay_ms(uint32_t ms) {
    uint32_t start = ms_count;
    while ((ms_count - start) < ms);
}

void delay_us(uint32_t us) {
    uint32_t start = us_count;
    while ((us_count - start) < us);
}