#include "relay.h"

void Relay_Init(void) {
    // Bật clock cho Relay
    Enable_GPIO_Clock(RELAY_PORT);

    // Thiết lập chân Relay là output push-pull 2MHz
    GPIO_SetPinMode(RELAY_PORT, RELAY_PIN, GPIO_MODE_OUTPUT_PP);
    
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