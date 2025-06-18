#include "uart.h"

void UART1_Init(void) {
    Enable_USART_Clock(USART1);
    Enable_GPIO_Clock(GPIOA); 

    GPIO_SetPinMode(GPIOA, 9, GPIO_MODE_AF_PP);          
    GPIO_SetPinMode(GPIOA, 10, GPIO_MODE_INPUT_FLOATING); 

    USART1->BRR = 0x1D2C; 
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; 
}

void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c; 
}

void UART1_SendString(const char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}
