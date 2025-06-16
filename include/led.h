#ifndef LED_H
#define LED_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>
#include <timer.h>
#include <stddef.h>

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