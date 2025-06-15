#include "rcc.h"

// Hàm cấu hình hệ thống clock lên 72MHz (HSE 8MHz * 9)
void SystemClock_Config(void) {
    // Bật HSE
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Cấu hình flash wait state
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // Cấu hình PLL: HSE * 9 = 72MHz
    RCC->CFGR |= RCC_CFGR_PLLSRC;      // PLL nguồn từ HSE
    RCC->CFGR |= RCC_CFGR_PLLMULL9;    // Nhân 9

    // Cấu hình prescaler cho APB1 (<=36MHz)
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Bật PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Chuyển hệ thống clock sang PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}