#pragma once
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

/**
 * @brief RTC pin that will interrupt when alarm will be triggered
 */
#define RTC_INT_PIN GPIO10
/**
 * @brief RTC port that will interrupt when alarm will be triggered
 */
#define RTC_INT_PORT GPIOA
/**
 * @brief Button to turn off alarm port
 */
#define BUTTON_OFFALARM_PORT GPIOB
/**
 * @brief Button to turn off alarm pin
 */
#define BUTTON_OFFALARM_PIN GPIO12
/**
 * @brief configure all exti and gpio
 */
void configure_exti(void);
