#ifndef ADC_H
#define ADC_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>
#include <delay.h>
#include <math.h>

#define RL     10.0f          
#define RO     10.0f          
#define A_BUTAN 108.98f       
#define B_BUTAN -2.174f

typedef enum {
    GAS_INIT = 0,
    GAS_NONE = 1,
    GAS_LOW = 2,
    GAS_HIGH = 3,
    GAS_DANGEROUS = 4
} GasState;

void ADC1_Init(void);
float ConvertToVoltage(uint16_t adcValue);
uint16_t ADC_Read(void);
float ConvertToPPM(uint16_t adcValue);

#endif // ADC_H
