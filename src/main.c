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
#include <nvic.h>
#include <switch.h>

int main(void) {
    char buffer[32];
    uint16_t adcValue;
    float ppmValue;

    SystemClock_Config();
    LED_Init();
    // Switch_Init();
    Buzzer_Init();
    Relay_Init();
    SysTick_Init(1000);
    TIM2_Init(1);
    UART_Init();
    ADC1_Init(); 
    I2C1_Init();
    OLED_Init();
    NVIC_ConfigPriorities();

    uint8_t current_state = 255; // giá trị bất hợp lệ ban đầu

    while (1) {
        adcValue = ADC_Read();
        ppmValue = ConvertToPPM(adcValue);
        
        char buffer2[16];
        sprintf(buffer2, "%d\n", (int)ppmValue);
        UART_SendString(buffer2);

        OLED_SetCursor(0, 0);
        OLED_WriteString("He thong: Dang hoat dong", Font_7x10, Black);
        snprintf(buffer, sizeof(buffer), "GAS: %u PPM", (unsigned int)ppmValue);
        OLED_SetCursor(0, 24);
        OLED_WriteString(buffer, Font_7x10, Black);

        uint8_t new_state;

        if (ppmValue < 200) {
            new_state = 0;
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Khong co khi gas", Font_7x10, Black);
        } else if (ppmValue < 300) {
            new_state = 1;
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas thap", Font_7x10, Black);
        } else if (ppmValue < 400) {
            new_state = 2;
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas cao", Font_7x10, Black);
        } else {
            new_state = 3;
            OLED_SetCursor(0, 36);
            OLED_WriteString("Trang thai: Nong do khi gas cao tren muc nguy hiem", Font_7x10, Black);
        }

        // Chỉ cập nhật hành vi LED/Buzzer/Relay nếu trạng thái thay đổi
        if (new_state != current_state) {
            current_state = new_state;

            switch (current_state) {
                case 0:
                    LED_Clear();
                    LED_On(LED_BLUE);
                    Relay_SetState(RELAY_OFF);
                    Buzzer_SetState(BUZZER_OFF);
                    break;
                case 1:
                    LED_Clear();
                    LED_On(LED_YELLOW);
                    Relay_SetState(RELAY_ON);
                    Buzzer_SetState(BUZZER_OFF);
                    break;
                case 2:
                    // Không clear LED, chỉ toggle
                    LED_Toggle(LED_RED, 1);
                    Relay_SetState(RELAY_ON);
                    Buzzer_SetState(BUZZER_ON);
                    break;
                case 3:
                    LED_Clear();
                    LED_Toggle(LED_RED, 5);
                    Relay_SetState(RELAY_ON);
                    Buzzer_SetState(BUZZER_ON);
                    break;
            }
        }

        OLED_UpdateScreen();
        delay_ms(1000);
    }
}