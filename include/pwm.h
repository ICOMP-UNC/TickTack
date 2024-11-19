#pragma once
#include "delay.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

/**
 * @brief D4 note frequency [Hz]
 */
#define D4 293
/**
 * @brief F4 note frequency [Hz]
 */
#define F4 349
/**
 * @brief A4 note frequency [Hz]
 */
#define A4 440
/**
 * @brief G4 note frequency [Hz]
 */
#define G4 392
/**
 * @brief Ab4 note frequency [Hz]
 */
#define Ab4 415
/**
 * @brief Bb4 note frequency [Hz]
 */
#define Bb4 466
/**
 * @brief D5 note frequency [Hz]
 */
#define D5 587
/**
 * @brief C5 note frequency [Hz]
 */
#define C5 523

/**
 * @brief Configure TIM1 to PWM function and portA9
 */
void configure_pwm(void);
/**
 * @brief Set frequency to pwm (because a pasive buzzer can sound in differents notes)
 * @param frequency to be setted
 */
void pwm_set_frequency(uint32_t frequency);
/**
 * @brief Start buzzer with specefied frequency
 * @param frequency to be setted
 */
void start_buzzer(uint32_t frequency);
/**
 * @brief stop the buzzer (stops TIM1)
 */
void stop_buzzer(void);
