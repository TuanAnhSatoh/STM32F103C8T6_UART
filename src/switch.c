#include "switch.h"

void Switch_Init(void) {
    Enable_GPIO_Clock(RESET_SW_PORT);
    Enable_GPIO_Clock(START_STOP_SW_PORT);

    GPIO_SetPinMode(RESET_SW_PORT, RESET_SWITCH_PIN, GPIO_MODE_INPUT_PULLDOWN);
    GPIO_SetPinMode(START_STOP_SW_PORT, START_STOP_SW_PIN, GPIO_MODE_INPUT_PULLDOWN);

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0 | AFIO_EXTICR1_EXTI1); 
    EXTI->IMR  |= (EXTI_IMR_MR0 | EXTI_IMR_MR1);
    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1); 

    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        EXTI->PR = EXTI_PR_PR0; 
        System_Reset(); 
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        EXTI->PR = EXTI_PR_PR1; 
        if (system_state == SYSTEM_RUNNING) {
            system_state = SYSTEM_STOPPED;
        } else {
            system_state = SYSTEM_RUNNING;
        }
    } 
}

