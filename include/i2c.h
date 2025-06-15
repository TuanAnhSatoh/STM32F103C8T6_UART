#ifndef I2C_H
#define I2C_H

#include <stm32f103xe.h>
#include <stdint.h>

void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_Stop(void);
void I2C1_Master_Transmit(uint8_t address, uint8_t *data, uint16_t size);

void I2C2_Init(void);
void I2C2_Start(void);
void I2C2_Stop(void);
void I2C2_Master_Transmit(uint8_t address, uint8_t *data, uint16_t size);

#endif // I2C_H