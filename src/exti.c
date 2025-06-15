#include "exti.h"

volatile SystemState_t system_state = SYSTEM_RUNNING;

// Hàm khởi tạo EXTI cho SW1 (PA0) và SW2 (PA1)
void EXTI_Init(void) {
    // Bật clock cho AFIO và GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;

    // Cấu hình PA0, PA1 là input floating
    SW1_PORT->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    SW1_PORT->CRL |= GPIO_CRL_CNF0_0; // Input floating

    SW2_PORT->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    SW2_PORT->CRL |= GPIO_CRL_CNF1_0; // Input floating

    // Kết nối EXTI0 với PA0, EXTI1 với PA1
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0; // PA0
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI1; // PA1

    // Cấu hình EXTI0, EXTI1: ngắt cạnh xuống (falling edge)
    EXTI->IMR  |= EXTI_IMR_MR0 | EXTI_IMR_MR1;   // Unmask EXTI0, EXTI1
    EXTI->FTSR |= EXTI_FTSR_TR0 | EXTI_FTSR_TR1; // Falling trigger

    // Bật NVIC cho EXTI0, EXTI1
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
}

// IRQHandler cho SW1 (PA0)
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        EXTI->PR = EXTI_PR_PR0; // Xóa cờ ngắt
        SW1_Callback();
    }
}

// IRQHandler cho SW2 (PA1)
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        EXTI->PR = EXTI_PR_PR1; // Xóa cờ ngắt
        SW2_Callback();
    }
}

// Callback cho SW1: chuyển đổi trạng thái hệ thống
void SW1_Callback(void) {
    if (system_state == SYSTEM_RUNNING) {
        system_state = SYSTEM_STOPPED;
        // Có thể thêm code để dừng giám sát, tắt LCD, v.v.
    } else {
        system_state = SYSTEM_RUNNING;
        // Có thể thêm code để tiếp tục giám sát, cập nhật LCD, v.v.
    }
}

// Callback cho SW2: reset trạng thái hệ thống về ban đầu
void SW2_Callback(void) {
    system_state = SYSTEM_STOPPED;
    // Có thể thêm code để reset bộ đếm, LCD, các biến khác về trạng thái ban đầu
}

