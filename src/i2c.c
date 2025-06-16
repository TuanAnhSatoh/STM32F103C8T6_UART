#include "i2c.h"

void I2C1_Init(void) {
    // Bật clock cho I2C1 và GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // PB6 (SCL), PB7 (SDA) - Alternate function open-drain, 50MHz
    GPIOB->CRL &= ~((0xF << (6 * 4)) | (0xF << (7 * 4)));
    GPIOB->CRL |=  ((0xB << (6 * 4)) | (0xB << (7 * 4))); // MODE=11 (50MHz), CNF=11 (AF OD)

    // Reset I2C1
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // Cấu hình tần số ngoại vi (APB1 = 36MHz)
    I2C1->CR2 = 36;

    // Cấu hình clock I2C = 100kHz (chuẩn)
    I2C1->CCR = 180;
    I2C1->TRISE = 37;

    // Enable I2C1
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
    // Chờ bus rảnh
    while (I2C1->SR2 & I2C_SR2_BUSY);

    // START
    I2C1_Start();

    // Gửi địa chỉ
    I2C1->DR = address; 
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    // Gửi dữ liệu
    for (uint16_t i = 0; i < size; i++) {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    // Chờ gửi xong
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    // STOP
    I2C1_Stop();
}