#include "delay.h"

void delay_micro(uint32_t micros)
{
    for (volatile uint32_t i = 0; i < micros * TICKS_TO_MICRO; i++)
    {
        __asm__("NOP");
    }
}

void delay_milli(uint32_t millis)
{

    for (volatile uint32_t i = 0; i < millis * TICKS_TO_MILLI; i++)
    {
        __asm__("NOP");
    }
}
