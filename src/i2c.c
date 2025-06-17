#include "i2c.h"

void I2C1_Init(void) {
    Enable_I2C_Clock(I2C1);
    Enable_GPIO_Clock(GPIOB);

    GPIO_SetPinMode(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_MODE_AF_OD); 
    GPIO_SetPinMode(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_MODE_AF_OD);

    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 36;
    I2C1->CCR = 180;
    I2C1->TRISE = 37;

    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
    (void)I2C1->SR1;
}

void I2C1_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C1_Master_Transmit(uint8_t address, uint8_t *data, uint16_t size) {
    while (I2C1->SR2 & I2C_SR2_BUSY);

    I2C1_Start();

    I2C1->DR = address; 
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    for (uint16_t i = 0; i < size; i++) {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1_Stop();
}