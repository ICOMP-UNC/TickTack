#pragma once
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

/**
 * @brief High voltage umbral to battery 
 */
#define HIGH_BAT_VALUE 3

/**
 * @brief MID voltage umbral to battery 
 * */
#define MID_BAT_VALUE 2.6
/**
 * @brief LOW voltage umbral to battery 
 * */
#define LOW_BAT_VALUE 2.3
/**
 * @brief bat value storage
 * */
extern volatile uint16_t bat_value;
/**
 * @brief adc setup
 * */
void configure_adc(void);

/**
 * @brief dma setup to send adc data to batvalue
 * */
void configure_dma(void);

/**
 * @brief timer3 to star adc convertion with match
 * */
void configure_timer3(void);

/**
 * @brief configure battery leds 
 * */
void configure_battery_leds(void);
