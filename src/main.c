#include <stm32f103xe.h>
#include <rcc.h>
#include <uart.h>
#include <timer.h>
#include <delay.h>
#include <i2c.h>
#include <oled.h>
#include <fonts.h>
#include <adc.h>
#include <led.h>
#include <stdio.h>
#include <buzzer.h>
#include <relay.h>

int main(void) {
    char buffer[32];
    uint16_t adcValue;

    SystemClock_Config();
    UART_Init();
    TIM2_Init(1000000);
    ADC1_Init(); 
    I2C1_Init();
    OLED_Init();
    LED_Init();
    Buzzer_Init();
    Relay_Init();

       while (1) {
        adcValue = ADC_Read();
        
        char buffer2[16];
        sprintf(buffer2, "%d\n", adcValue);  // thêm \n

        UART_SendString(buffer2);

        OLED_SetCursor(0, 0);
        OLED_WriteString("He thong: Dang hoat dong", Font_7x10, Black);
    
        snprintf(buffer, sizeof(buffer), "GAS: %u PPM", adcValue);
        OLED_SetCursor(0, 24); // Dòng thứ 2, Y = 12 cho thoáng
        OLED_WriteString(buffer, Font_7x10, Black);
    
        if (adcValue < 200) {
            OLED_SetCursor(0, 36); // Dòng thứ 3
            OLED_WriteString("Trang thai: Khong co khi gas", Font_7x10, Black);
            LED_Clear(); // Tắt tất cả đèn LED
            LED_On(LED_BLUE);
            Buzzer_SetState(BUZZER_OFF); // Tắt buzzer 
            Relay_SetState(RELAY_OFF); // Tắt relay nếu có
        } else if (adcValue < 400) {
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas thap", Font_7x10, Black);
            Buzzer_SetState(BUZZER_ON); // Bật buzzer
            Relay_SetState(RELAY_ON); // Bật relay nếu có
            LED_Clear(); // Tắt tất cả đèn LED
            LED_On(LED_YELLOW);

        } else if (adcValue < 600) {
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas cao", Font_7x10, Black);
            Buzzer_SetState(BUZZER_ON); // Bật buzzer
            Relay_SetState(RELAY_ON); // Bật relay nếu có
            // LED_Clear(); // Tắt tất cả đèn LED
            LED_Toggle(LED_RED, 1); 
        } else {
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas cao tren muc nguy hiem", Font_7x10, Black);
            Buzzer_SetState(BUZZER_ON); // Bật buzzer
            Relay_SetState(RELAY_ON); // Bật relay nếu có
            LED_Clear(); // Tắt tất cả đèn LED
            LED_Toggle(LED_RED, 10); 
        }
        OLED_UpdateScreen();
    
        delay_ms(1000);
    }
}