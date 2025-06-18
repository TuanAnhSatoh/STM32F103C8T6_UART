#include <system.h>

volatile SystemState system_state = SYSTEM_RUNNING;

void System_Init(void) {
    SystemClock_Config();
    SysTick_Init(1);
    TIM2_Init(1);
    UART1_Init();
    ADC1_Init();
    I2C1_Init();
    LED_Init();
    OLED_Init();
    Buzzer_Init();
    Relay_Init();
    Switch_Init();
    NVIC_ConfigPriorities();
}

void System_Reset(void) {
    NVIC_SystemReset();
}