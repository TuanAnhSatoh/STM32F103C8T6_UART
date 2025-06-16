#ifndef UART_H
#define UART_H

#include <stm32f103xe.h>
#include <pinmap.h>
#include <gpio.h>
#include <rcc.h>

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(const char *str);

#endif // UART_H
