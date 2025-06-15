#include "buzzer.h"

void Buzzer_Init(void) {
    // Bật clock cho GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Xóa các bit MODE1 và CNF1
    BUZZER_PORT->CRL &= ~((0xF) << (1 * 4)); // Xóa 4 bit tại vị trí PA1

    // MODE1 = 0b10 (output 2MHz), CNF1 = 0b00 (push-pull)
    BUZZER_PORT->CRL |= (0x2 << (1 * 4)); // MODE1 = 0b10, CNF1 = 0b00

    // Đặt buzzer về trạng thái OFF mặc định
    Buzzer_SetState(BUZZER_OFF);
}

void Buzzer_SetState(Buzzer_State_t state) {
    if (state == BUZZER_ON) {
        GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
    } else {
        GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
    }
}