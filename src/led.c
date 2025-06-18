#include "led.h"

static volatile LED_Color_t led_toggle_color;

void LED_Init(void) {
    Enable_GPIO_Clock(RED_LED_PORT);
    Enable_GPIO_Clock(GREEN_LED_PORT); 
    Enable_GPIO_Clock(BLUE_LED_PORT);

    GPIO_SetPinMode(RED_LED_PORT, RED_LED_PIN, GPIO_MODE_OUTPUT_PP);
    GPIO_SetPinMode(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_MODE_OUTPUT_PP);    
    GPIO_SetPinMode(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_MODE_OUTPUT_PP);

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
    switch (led_toggle_color) {
        case LED_RED:
            GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
            break;
        case LED_GREEN:
            GPIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
            break;
        case LED_BLUE:
            GPIO_TogglePin(BLUE_LED_PORT, BLUE_LED_PIN);
            break;
        case LED_YELLOW:
            GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
            GPIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
            break;
        default:
            break;
    }
}

void LED_Toggle(LED_Color_t color, uint16_t ppmValue) {
    uint32_t frequency;

    if (ppmValue < 35) {
        frequency = 1; 
    } else {
        const uint16_t ppm_min = 35;
        const uint16_t ppm_max = 100;
        const uint8_t freq_min = 2;
        const uint8_t freq_max = 10;

        float scale = (float)(freq_max - freq_min) / (ppm_max - ppm_min);
        frequency = freq_min + (uint32_t)((ppmValue - ppm_min) * scale);

        if (frequency > freq_max) {
            frequency = freq_max;
        }
    }

    LED_Clear(); 
    led_toggle_color = color;
    TIM2_SetCallback(Led_Toggle_Callback);
    TIM2_Init(frequency);
}

void LED_StopToggle(void) {
    TIM2_Stop(); 
    LED_Clear();
}



