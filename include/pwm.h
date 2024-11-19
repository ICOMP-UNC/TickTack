#pragma once
#include "delay.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
extern uint32_t pwm_freq;
void configure_pwm(void);
void pwm_set_frequency(uint32_t frequency);
void start_buzzer(uint32_t frequency);
void stop_buzzer();
void play_note(uint32_t frequency, uint32_t duration);
