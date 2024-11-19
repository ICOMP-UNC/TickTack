#pragma once
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#define HIGH_BAT_VALUE 3
#define MID_BAT_VALUE 2.6
#define LOW_BAT_VALUE 2.3

extern volatile uint16_t bat_value;
void configure_adc(void);
void configure_dma(void);
void configure_timer3(void);
void configure_battery_leds(void);
