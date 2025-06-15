#include "relay.h"

void Relay_Init(void) {
    // Bật clock cho GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Xóa các bit MODE8 và CNF8 (trong CRH, vì PA8)
    RELAY_PORT->CRH &= ~((0xF) << ((8 - 8) * 4)); // Xóa 4 bit tại vị trí PA8 (offset 0)
    // MODE8 = 0b10 (output 2MHz), CNF8 = 0b00 (push-pull)
    RELAY_PORT->CRH |= (0x2 << ((8 - 8) * 4));    // MODE8 = 0b10, CNF8 = 0b00

    // Đặt relay về trạng thái OFF mặc định
    Relay_SetState(RELAY_OFF);
}

void Relay_SetState(Relay_State_t state) {
    if (state == RELAY_ON) {
        GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
    } else {
        GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
    }
}