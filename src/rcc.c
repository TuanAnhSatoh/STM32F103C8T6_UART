#include "rcc.h"

void SystemClock_Config(void) {
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    RCC->CFGR |= RCC_CFGR_PLLSRC;    
    RCC->CFGR |= RCC_CFGR_PLLMULL9;    

    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void Enable_GPIO_Clock(GPIO_TypeDef *PORT) {
    if (PORT == GPIOA) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    } else if (PORT == GPIOB) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    } else if (PORT == GPIOC) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    } else if (PORT == GPIOD) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
    } else if (PORT == GPIOE) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
    }
}

void Enable_I2C_Clock(I2C_TypeDef *I2Cx) {
    if (I2Cx == I2C1) {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    } else if (I2Cx == I2C2) {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    }
}

void Enable_USART_Clock(USART_TypeDef *USARTx) {
    if (USARTx == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    else if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    else if (USARTx == USART3) RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
}

void Enable_AFIO_Clock(void) {
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

void Enable_TIMER_Clock(TIM_TypeDef *TIMx) {
    if (TIMx == TIM1)  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if (TIMx == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIMx == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if (TIMx == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}

void Enable_ADC_Clock(ADC_TypeDef *ADCx) {
    if (ADCx == ADC1) {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    } else if (ADCx == ADC2) {
        RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
    }
}
