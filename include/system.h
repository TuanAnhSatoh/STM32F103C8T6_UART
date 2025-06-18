#ifndef SYSTEM_H
#define SYSTEM_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>
#include <delay.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fonts.h>
#include <oled.h>
#include <adc.h>
#include <led.h>
#include <buzzer.h>
#include <relay.h>
#include <nvic.h>
#include <uart.h>
#include <switch.h>
#include <i2c.h>
#include <timer.h>
#include <systick.h>

typedef enum {
    SYSTEM_STOPPED = 0,
    SYSTEM_RUNNING = 1
} SystemState;

extern volatile SystemState system_state;

void System_Init(void);
void System_Reset(void);

#endif // SYSTEM_H