#ifndef SWITCH_H
#define SWITCH_H

#include <stm32f103xe.h>
#include <gpio.h>
#include <pinmap.h>

#define SWITCH_RESET_PORT GPIOA
#define SWITCH_RESET_PIN GPIO_PIN_0

#define SWITCH_START_STOP_PORT GPIOA
#define SWITCH_START_STOP_PIN GPIO_PIN_1

#endif // SWITCH_H