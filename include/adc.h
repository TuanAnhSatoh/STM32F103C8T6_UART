#ifndef ADC_H
#define ADC_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>
#include <delay.h>

void ADC1_Init(void);
float ConvertToVoltage(uint16_t adcValue);
uint16_t ADC_Read(void);

#endif // ADC_H
