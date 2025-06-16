#ifndef RCC_H
#define RCC_H

#include <stm32f103xe.h>

void SystemClock_Config(void);

void Enable_GPIO_Clock(GPIO_TypeDef *PORT);
void Enable_I2C_Clock(I2C_TypeDef *I2Cx);
void Enable_USART_Clock(USART_TypeDef *USARTx);
void Enable_AFIO_Clock(void);
void Enable_TIMER_Clock(TIM_TypeDef *TIMx);
void Enable_ADC_Clock(ADC_TypeDef *ADCx);

#endif // RCC_H
