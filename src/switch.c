#include "switch.h"

void Switch_Init(void) {
    // Bật clock cho GPIOA
    Enable_GPIO_Clock(RESET_SW_PORT);
    Enable_GPIO_Clock(START_STOP_SW_PORT);

    // Cấu hình PA0 (RESET) và PA1 (START_STOP) là input pull-down
    GPIO_SetPinMode(RESET_SW_PORT, RESET_SWITCH_PIN, GPIO_MODE_INPUT_PULLDOWN);
    GPIO_SetPinMode(START_STOP_SW_PORT, START_STOP_SW_PIN, GPIO_MODE_INPUT_PULLDOWN);
}

