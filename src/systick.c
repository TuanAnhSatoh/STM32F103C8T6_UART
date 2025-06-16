#include "systick.h"

void SysTick_Init(uint32_t tick_us) {
    uint32_t ticks = (SystemCoreClock / 1000000) * tick_us;  // số chu kỳ giữa các ngắt

    SysTick->LOAD  = ticks - 1;                // Giá trị đếm
    SysTick->VAL   = 0;                        // Reset bộ đếm hiện tại
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |  // Sử dụng HCLK (72MHz)
                     SysTick_CTRL_TICKINT_Msk   |  // Cho phép ngắt
                     SysTick_CTRL_ENABLE_Msk;     // Bắt đầu SysTick
}