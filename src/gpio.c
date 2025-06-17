#include "gpio.h"

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint16_t pin, uint32_t mode) {
    uint32_t shift = (pin % 8) * 4;
    volatile uint32_t *config = (pin < 8) ? &GPIOx->CRL : &GPIOx->CRH;

    *config &= ~(0xF << shift);  

    switch (mode) {
        case GPIO_MODE_INPUT_FLOATING: 
            *config |= (0x04 << shift); 
            break;
        case GPIO_MODE_INPUT_PULLUP:   
            *config |= (0x08 << shift); 
            GPIOx->BSRR = (1U << pin);  
            break;
        case GPIO_MODE_INPUT_PULLDOWN: 
            *config |= (0x08 << shift); 
            GPIOx->BRR = (1U << pin);   
            break;
        case GPIO_MODE_ANALOG:         
            *config |= (0x00 << shift); 
            break;
        case GPIO_MODE_OUTPUT_PP:      
            *config |= (0x01 << shift); 
            break;
        case GPIO_MODE_OUTPUT_OD:      
            *config |= (0x05 << shift); 
            break;
        case GPIO_MODE_AF_PP:          
            *config |= (0x09 << shift); 
            break;
        case GPIO_MODE_AF_OD:        
            *config |= (0x0D << shift); 
            break;
        default:
            break;
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t value) {
    if (value) {
        GPIOx->BSRR = (1U << pin);
    } else {
        GPIOx->BRR = (1U << pin);
    }
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t pin) {
    GPIOx->ODR ^= (1U << pin);
}