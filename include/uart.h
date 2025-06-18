#ifndef UART_H
#define UART_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>

void UART1_Init(void);
void UART1_SendChar(char c);
void UART1_SendString(const char *str);

#endif // UART_H
