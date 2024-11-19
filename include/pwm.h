#pragma once
#include "delay.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#define D4 293
#define F4 349
#define A4 440
#define G4 392
#define Ab4 415
#define Bb4 466
#define D5 587
#define C5 523

void configure_pwm(void);
void pwm_set_frequency(uint32_t frequency);
void start_buzzer(uint32_t frequency);
void stop_buzzer(void);
void play_note(uint32_t frequency, uint32_t duration);
