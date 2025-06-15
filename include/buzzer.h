#ifndef BUZZER_H
#define BUZZER_H

#include <stm32f103xe.h>
#include <gpio.h>
#include <pinmap.h>

#define BUZZER_PORT GPIOA
#define BUZZER_PIN GPIO_PIN_1

typedef enum {
    BUZZER_OFF,
    BUZZER_ON
} Buzzer_State_t;

void Buzzer_Init(void);
void Buzzer_SetState(Buzzer_State_t state);

#endif // BUZZER_H