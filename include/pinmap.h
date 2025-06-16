#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include "stm32f103xe.h"

// LED pins
#define RED_LED_PORT         GPIOA
#define RED_LED_PIN          5

#define GREEN_LED_PORT       GPIOA
#define GREEN_LED_PIN        4

#define BLUE_LED_PORT        GPIOA
#define BLUE_LED_PIN         3

// UART1 pins PA10 RX, PA9 TX
#define ESP32_UART         USART1

#define UART_RX_PORT      GPIOA
#define UART_RX_PIN       10

#define UART_TX_PORT      GPIOA
#define UART_TX_PIN       9


// BUTTONS
#define RESET_SW_PORT           GPIOA
#define RESET_SWITCH_PIN        0

#define START_STOP_SW_PORT      GPIOA
#define START_STOP_SW_PIN       1

//TIMER
#define LED_TIMER                TIM2
#define LED_TIMER_IRQn           TIM2_IRQn

//Buzzer
#define BUZZER_PORT         GPIOA
#define BUZZER_PIN          7

//Relay
#define RELAY_PORT          GPIOA
#define RELAY_PIN           8

//OLED
#define OLED_SCL_PORT       GPIOB
#define OLED_SCL_PIN        6

#define OLED_SDA_PORT       GPIOB
#define OLED_SDA_PIN        7

//ADC
#define GAS_ADC             ADC1
#define ADC_PORT            GPIOA
#define ADC_PIN             6
#define ADC_CHANNEL         6

#endif // PIN_CONFIG_H