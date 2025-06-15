#ifndef LED_H
#define LED_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <timer.h>
#include <stddef.h>

#define RED_LED_PORT    GPIOA
#define RED_LED_PIN     GPIO_PIN_5

#define GREEN_LED_PORT  GPIOA
#define GREEN_LED_PIN   GPIO_PIN_4

#define BLUE_LED_PORT   GPIOA
#define BLUE_LED_PIN    GPIO_PIN_3

typedef enum {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW
} LED_Color_t;

void LED_Init(void);
void LED_Clear(void);
void LED_On(LED_Color_t color);
void LED_Toggle(LED_Color_t color, uint32_t frequency);
void LED_StopToggle(void);

#endif // LED_H