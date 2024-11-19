#include "delay.h"
#include "timer_cfg.h"

void delay_micro(uint32_t micros)
{
    uint16_t start = timer_get_counter(TIM2);
    while ((uint16_t)(timer_get_counter(TIM2) - start) < micros)
        ;
}

void delay_millis(uint32_t millis)
{
    for (uint32_t i = 0; i < millis; i++)
    {
        delay_micro(1000); // 1 ms = 1000 µs
    }
}
