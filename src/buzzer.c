#include "buzzer.h"

void Buzzer_Init(void) {
    Enable_GPIO_Clock(BUZZER_PORT);
    GPIO_SetPinMode(BUZZER_PORT, BUZZER_PIN, GPIO_MODE_OUTPUT_PP);
    Buzzer_SetState(BUZZER_OFF);
}

void Buzzer_SetState(Buzzer_State_t state) {
    if (state == BUZZER_ON) {
        GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
    } else {
        GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
    }
}