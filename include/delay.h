#pragma once
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
 * @brief delay loop in microseconds
 * @param micros micro seconds to wait
 */
void delay_micro(uint32_t micros);

/**
 * @brief ticks to micro seconds for delay loop
 * @param millis milli seconds to wait
 */
void delay_milli(uint32_t millis);
