#ifndef RELAY_H
#define RELAY_H

#include <stm32f103xe.h>
#include <gpio.h>
#include <rcc.h>
#include <pinmap.h>

typedef enum {
    RELAY_OFF,
    RELAY_ON
} Relay_State_t;

void Relay_Init(void);
void Relay_SetState(Relay_State_t state);

#endif // RELAY_H