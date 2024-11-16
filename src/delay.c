#include "delay.h"

void delay(uint32_t ticks)
{
    for (volatile uint32_t i = 0; i < ticks; i++)
    {
        __asm__("NOP");
    }
}
