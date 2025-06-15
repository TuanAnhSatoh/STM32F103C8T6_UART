#include "uart.h"

void UART_Init(void) {
    // Bật clock cho USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Bật clock cho GPIOA

    // Cấu hình PA9 (TX) và PA10 (RX) cho USART1
    GPIOA->CRH &= ~(0xF << 4); // Xóa cấu hình cũ
    GPIOA->CRH |= (0xB << 4);  // PA9: Alternate function push-pull, max speed 50MHz
    GPIOA->CRH |= (0x4 << 8);  // PA10: Input floating

    // Cấu hình USART1
    USART1->BRR = 0x1D2C; // Baud rate 9600 @ 72MHz
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; // Enable TX, RX and USART
}

void UART_SendChar(char c) {
    // Chờ cho TXE (Transmit Data Register Empty) bit được set
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c; // Gửi ký tự
}

void UART_SendString(const char *str) {
    while (*str) {
        UART_SendChar(*str++); // Gửi từng ký tự trong chuỗi
    }
}
