#include "switch.h"

void Switch_Init(void) {
    // Bật clock cho GPIOA
    Enable_GPIO_Clock(RESET_SW_PORT);
    Enable_GPIO_Clock(START_STOP_SW_PORT);

    // Cấu hình PA0 (RESET) và PA1 (START_STOP) là input pull-down
    GPIO_SetPinMode(RESET_SW_PORT, RESET_SWITCH_PIN, GPIO_MODE_INPUT_PULLDOWN);
    GPIO_SetPinMode(START_STOP_SW_PORT, START_STOP_SW_PIN, GPIO_MODE_INPUT_PULLDOWN);

    // Bật clock cho AFIO để cấu hình EXTI
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // Gán EXTI0 và EXTI1 cho PA0 và PA1
    AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0 | AFIO_EXTICR1_EXTI1); // PA0, PA1

    // Cho phép ngắt trên EXTI0 và EXTI1
    EXTI->IMR  |= (EXTI_IMR_MR0 | EXTI_IMR_MR1);

    // Ngắt cạnh xuống (nhấn nút)
    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1); 
}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        EXTI->PR = EXTI_PR_PR0; // Xóa cờ ngắt
        // Xử lý khi nhấn RESET switch tại đây
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        EXTI->PR = EXTI_PR_PR1; // Xóa cờ ngắt
        // Xử lý khi nhấn START/STOP switch tại đây
    }
}

