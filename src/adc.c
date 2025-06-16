#include "adc.h"

void ADC1_Init(void) {
    // Bật clock cho GPIOA và ADC1
    Enable_GPIO_Clock(GPIOA);
    Enable_ADC_Clock(ADC1);

    // PA6 là input analog
    GPIO_SetPinMode(ADC_PORT, ADC_PIN, GPIO_MODE_ANALOG);

    // Prescaler ADC = /6 (ADCCLK = 12MHz)
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_ADCPRE) | RCC_CFGR_ADCPRE_DIV6;

    // Bật ADC và delay nhỏ
    ADC1->CR2 |= ADC_CR2_ADON;
    delay_ms(25);

    // Thời gian lấy mẫu cho channel 6 (13.5 cycles)
    ADC1->SMPR2 = (ADC1->SMPR2 & ~ADC_SMPR2_SMP6) | ADC_SMPR2_SMP6_1;

    // 1 channel, chọn channel 6 (PA6)
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR3 = (ADC1->SQR3 & ~ADC_SQR3_SQ1) | (ADC_CHANNEL << 0);

    // Chế độ continuous, không scan
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT;

    // Cân chỉnh ADC
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    // Bắt đầu chuyển đổi
    ADC1->CR2 |= ADC_CR2_ADON;
}

float ConvertToVoltage(uint16_t adcValue) {
    return ((float)adcValue * 3.3f) / 4095.0f;
}

uint16_t ADC_Read(void) {
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}