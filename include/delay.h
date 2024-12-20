#pragma once
#include "timer_cfg.h"
#include <stdio.h>

/**
 * @brief ticks to micro seconds for delay loop
 */
#define TICKS_TO_MICRO 72
/**
 * @brief ticks to milli seconds for delay loop
 */
#define TICKS_TO_MILLI 72000

/**
 * @brief delay loop in microseconds (Uses timer2)
 * @param micros micro seconds to wait
 */
void delay_micro(uint32_t micros);

/**
 * @brief milliseconds delay (Uses timer2)
 * @param millis milli seconds to wait
 */
void delay_millis(uint32_t millis);
