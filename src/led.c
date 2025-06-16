#include "led.h"

static LED_Color_t toggle_color;

void LED_Init(void) {
    // Bật clock cho LED ports
    Enable_GPIO_Clock(RED_LED_PORT);
    Enable_GPIO_Clock(GREEN_LED_PORT); 
    Enable_GPIO_Clock(BLUE_LED_PORT);

    // Thiết lập PA5, PA4, PA3 là output push-pull 2MHz
    GPIO_SetPinMode(RED_LED_PORT, RED_LED_PIN, GPIO_MODE_OUTPUT_PP);
    GPIO_SetPinMode(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_MODE_OUTPUT_PP);    
    GPIO_SetPinMode(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_MODE_OUTPUT_PP);
    
    // Tắt tất cả LED
    GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);
    GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_RESET);
    GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PIN_RESET);
}

void LED_Clear(void) {
    GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);
    GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_RESET);
    GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PIN_RESET);
}

void LED_On(LED_Color_t color) {
    LED_StopToggle(); 
    switch (color) {
        case LED_RED:
            GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_SET);
            break;
        case LED_GREEN:
            GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_SET);
            break;
        case LED_BLUE:
            GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PIN_SET);
            break;
        case LED_YELLOW:
            GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_SET);
            GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}

static void Led_Toggle_Callback(void) {
    switch (toggle_color) {
        case LED_RED:
            RED_LED_PORT->ODR ^= RED_LED_PIN;
            break;
        case LED_GREEN:
            GREEN_LED_PORT->ODR ^= GREEN_LED_PIN;
            break;
        case LED_BLUE:
            BLUE_LED_PORT->ODR ^= BLUE_LED_PIN;
            break;
        case LED_YELLOW:
            RED_LED_PORT->ODR ^= RED_LED_PIN;
            GREEN_LED_PORT->ODR ^= GREEN_LED_PIN;
            break;
        default:
            break;
    }
}

void LED_Toggle(LED_Color_t color, uint32_t frequency) { 
    TIM3_Stop();
    toggle_color = color;
    LED_Clear(); 
    TIM3_SetCallback(Led_Toggle_Callback);
    TIM3_Init(frequency * 2);
    TIM3_Start();
}

void LED_StopToggle(void) {
    TIM3_Stop();
    TIM3_SetCallback(NULL);
    LED_Clear();
}

