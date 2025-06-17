#include "relay.h"

void Relay_Init(void) {
    Enable_GPIO_Clock(RELAY_PORT);
    GPIO_SetPinMode(RELAY_PORT, RELAY_PIN, GPIO_MODE_OUTPUT_PP);
}

void Relay_SetState(Relay_State_t state) {
    if (state == RELAY_ON) {
        GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
    } else {
        GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
    }
}