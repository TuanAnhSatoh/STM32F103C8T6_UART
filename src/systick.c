#include "systick.h"

void SysTick_Init(uint32_t tick_us) {
    uint32_t ticks = (SystemCoreClock / 1000000) * tick_us;  

    SysTick->LOAD  = ticks - 1;                
    SysTick->VAL   = 0;                        
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |  
                     SysTick_CTRL_TICKINT_Msk   |  
                     SysTick_CTRL_ENABLE_Msk;     
}