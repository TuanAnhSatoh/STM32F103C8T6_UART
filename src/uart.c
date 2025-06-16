#include "uart.h"

void UART_Init(void) {
    // Bật clock cho USART1
    Enable_USART_Clock(USART1);
    Enable_GPIO_Clock(GPIOA); // Bật clock cho GPIOA

    // Cấu hình PA9 (TX) và PA10 (RX) cho USART1
    GPIO_SetPinMode(UART_TX_PORT, UART_TX_PIN, GPIO_MODE_AF_PP); // TX: Alternate Function Push-Pull
    GPIO_SetPinMode(UART_RX_PORT, UART_RX_PIN, GPIO_MODE_INPUT); // RX: Input

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
