#include "gpio.h"

void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint16_t pin, uint32_t mode) {
    uint32_t shift = (pin % 8) * 4;
    volatile uint32_t *config = (pin < 8) ? &GPIOx->CRL : &GPIOx->CRH;

    *config &= ~(0xF << shift);  // Clear

    switch (mode) {
        case GPIO_MODE_INPUT:
            *config |= (0x04 << shift); // MODE = 00, CNF = 01 => floating input
            break;
        case GPIO_MODE_OUTPUT_PP:
            *config |= (0x01 << shift); // MODE = 01, CNF = 00 => output push-pull 10MHz
            break;
        case GPIO_MODE_OUTPUT_OD:
            *config |= (0x05 << shift); // MODE = 01, CNF = 01
            break;
        case GPIO_MODE_AF_PP:
            *config |= (0x09 << shift); // MODE = 01, CNF = 10
            break;
        case GPIO_MODE_AF_OD:
            *config |= (0x0D << shift); // MODE = 01, CNF = 11
            break;
        case GPIO_MODE_ANALOG:
            *config |= (0x00 << shift); // MODE = 00, CNF = 00
            break;
        case GPIO_MODE_INPUT_PU:
            *config |= (0x08 << shift); // MODE = 00, CNF = 10 => input pull-up
            GPIOx->BSRR = (1U << pin);   // Set the pin high
            break;
        case GPIO_MODE_INPUT_PD:
            *config |= (0x0C << shift); // MODE = 00, CNF = 11 => input pull-down
            GPIOx->BRR = (1U << pin);    // Set the pin low
            break;
        case GPIO_MODE_INPUT_PULLDOWN:
            *config |= (0x04 << shift); // MODE = 00, CNF = 01 => input pull-down
            GPIOx->BRR = (1U << pin);    // Set the pin low
            break;
        case GPIO_MODE_INPUT_PULLUP:
            *config |= (0x08 << shift); // MODE = 00, CNF = 10 => input pull-up
            GPIOx->BSRR = (1U << pin);   // Set the pin high
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

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t pin) {
    return (GPIOx->IDR & (1U << pin)) ? 1 : 0;
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t pin) {
    GPIOx->ODR ^= (1U << pin);
}