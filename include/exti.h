#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include <stm32f103xe.h>

// Định nghĩa chân kết nối nút nhấn
#define SW1_PIN        GPIO_PIN_0
#define SW1_PORT       GPIOA
#define SW2_PIN        GPIO_PIN_1
#define SW2_PORT       GPIOA

typedef enum {
    SYSTEM_STOPPED = 0,
    SYSTEM_RUNNING = 1
} SystemState_t;

void EXTI_Init(void);
void SW1_Callback(void);
void SW2_Callback(void);

#endif // EXTI_H