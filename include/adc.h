#ifndef ADC_H
#define ADC_H

#include <stm32f103xe.h>
#include <pinmap.h>

#define ADC_PIN GPIO_PIN_6 
#define ADC_CHANNEL 6

void ADC1_Init(void);
float ConvertToVoltage(uint16_t adcValue);
uint16_t ADC_Read(void);

#endif // ADC_H
