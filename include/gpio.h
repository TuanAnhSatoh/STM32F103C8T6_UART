#ifndef GPIO_H
#define GPIO_H

#include <stm32f103xe.h>

#define GPIO_MODE_INPUT       0x00U  
#define GPIO_MODE_ANALOG      0x01U
#define GPIO_MODE_INPUT_PU    0x02U  
#define GPIO_MODE_INPUT_PD    0x03U
#define GPIO_MODE_OUTPUT_PP   0x10U
#define GPIO_MODE_OUTPUT_OD   0x11U
#define GPIO_MODE_AF_PP       0x12U
#define GPIO_MODE_AF_OD       0x13U

#define GPIO_PIN_SET                1U
#define GPIO_PIN_RESET              0U

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint16_t pin, uint32_t mode);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t value);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif // GPIO_H