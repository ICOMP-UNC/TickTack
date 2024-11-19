#include "timer_cfg.h"
void configure_timer(void)
{
    // Habilitar reloj para TIM2
    rcc_periph_clock_enable(RCC_TIM2);

    timer_set_prescaler(TIM2, 72 - 1); // 72 MHz / 72 = 1 MHz (1 tick = 1 µs)
    timer_set_period(TIM2, 0xFFFF);    // Máximo período
    timer_enable_counter(TIM2);
}
