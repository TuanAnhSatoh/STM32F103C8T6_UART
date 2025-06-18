#include <stm32f103xe.h>
#include <system.h>

int main(void) {
    char buffer[32];
    uint16_t adcValue;
    float ppmValue;

    System_Init();

    GasState current_state = GAS_INIT;

    while (1) {
        if (system_state == SYSTEM_STOPPED) {
            LED_Clear();
            LED_On(LED_YELLOW);
            Relay_SetState(RELAY_OFF);
            Buzzer_SetState(BUZZER_OFF);
            OLED_Fill(Black);
            OLED_SetCursor(0, 0);
            OLED_WriteString("System", Font_7x10, Black);
            OLED_SetCursor(25, 20);
            OLED_WriteString("STOPPED", Font_11x18, Black);
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
        OLED_SetCursor(0, 20);
        OLED_WriteString(buffer, Font_11x18, Black);
        OLED_UpdateScreen();
        OLED_SetCursor(0, 48);

        GasState new_state;
        if (ppmValue < 100) {
            new_state = GAS_NONE;
            OLED_WriteString("State: GAS NONE", Font_7x10, Black);
        } else if (ppmValue < 200) {
            new_state = GAS_LOW;
            OLED_WriteString("State: GAS LOW", Font_7x10, Black);
        } else if (ppmValue < 350) {
            new_state = GAS_HIGH;
            OLED_WriteString("State: GAS HIGH", Font_7x10, Black);
        } else {
            new_state = GAS_DANGEROUS;
            OLED_WriteString("State: GAS DANGER", Font_7x10, Black);
        }

        OLED_UpdateScreen();

        if (new_state != current_state) {
            current_state = new_state;
        }
        
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
                LED_Toggle(LED_RED, (uint16_t)ppmValue); 
                Relay_SetState(RELAY_ON);
                Buzzer_SetState(BUZZER_ON);
                break;
            case GAS_DANGEROUS:
                LED_Toggle(LED_RED, (uint16_t)ppmValue);
                Relay_SetState(RELAY_ON);
                Buzzer_SetState(BUZZER_ON);
                break;
            default:
                break;
        }
    }
}