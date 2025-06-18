#include <stm32f103xe.h>
#include <system.h>

int main(void) {
    char buffer[32];
    uint16_t adcValue;
    float ppmValue;

    System_Init();

    GasState current_state = GAS_NONE;

    while (1) {
        if (system_state == SYSTEM_STOPPED) {
            LED_Clear();
            LED_On(LED_YELLOW);
            Relay_SetState(RELAY_OFF);
            Buzzer_SetState(BUZZER_OFF);
            OLED_SetCursor(12, 12);
            OLED_WriteString("System: STOPPED", Font_11x18, Black);
            OLED_UpdateScreen();
            delay_ms(500);
            continue;
        }

        adcValue = ADC_Read();
        ppmValue = ConvertToPPM(adcValue);

        char buffer2[16];
        sprintf(buffer2, "%d\n", (int)ppmValue);
        UART1_SendString(buffer2);

        OLED_SetCursor(0, 0);
        OLED_WriteString("System: RUNNING", Font_7x10, Black);
        snprintf(buffer, sizeof(buffer), "GAS: %u PPM", (unsigned int)ppmValue);
        OLED_SetCursor(0, 24);
        OLED_WriteString(buffer, Font_7x10, Black);
        OLED_SetCursor(0, 36);

        GasState new_state;
        if (ppmValue < 100) {
            new_state = GAS_NONE;
            OLED_WriteString("GAS: NONE", Font_7x10, Black);
        } else if (ppmValue < 200) {
            new_state = GAS_LOW;
            OLED_WriteString("GAS: LOW", Font_7x10, Black);
        } else if (ppmValue < 350) {
            new_state = GAS_HIGH;
            OLED_WriteString("GAS: HIGH", Font_7x10, Black);
        } else {
            new_state = GAS_DANGEROUS;
            OLED_WriteString("GAS: DANGEROUS", Font_7x10, Black);
        }
        
        if (new_state != current_state) {
            current_state = new_state;
            switch (current_state) {
                case GAS_NONE:
                    LED_On(LED_BLUE);
                    Relay_SetState(RELAY_OFF);
                    Buzzer_SetState(BUZZER_OFF);
                    break;
                case GAS_LOW:
                    LED_On(LED_YELLOW);
                    Relay_SetState(RELAY_OFF);
                    Buzzer_SetState(BUZZER_OFF);
                    break;
                case GAS_HIGH:
                    LED_Toggle(LED_RED, 1); 
                    Relay_SetState(RELAY_ON);
                    Buzzer_SetState(BUZZER_ON);
                    break;
                case GAS_DANGEROUS:
                    LED_Toggle(LED_RED, 2);
                    Relay_SetState(RELAY_ON);
                    Buzzer_SetState(BUZZER_ON);
                    break;
            }
        }
    }
}