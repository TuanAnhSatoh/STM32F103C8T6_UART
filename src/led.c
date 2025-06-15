#include "led.h"

static LED_Color_t toggle_color;

void LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRL &= ~((GPIO_CRL_MODE5 | GPIO_CRL_CNF5) |
                    (GPIO_CRL_MODE4 | GPIO_CRL_CNF4) |
                    (GPIO_CRL_MODE3 | GPIO_CRL_CNF3));
    GPIOA->CRL |=  ((0x2 << GPIO_CRL_MODE5_Pos) | 
                    (0x0 << GPIO_CRL_CNF5_Pos)  | 
                    (0x2 << GPIO_CRL_MODE4_Pos) |
                    (0x0 << GPIO_CRL_CNF4_Pos)  |
                    (0x2 << GPIO_CRL_MODE3_Pos) |
                    (0x0 << GPIO_CRL_CNF3_Pos));
    
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

