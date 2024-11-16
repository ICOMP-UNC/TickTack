#pragma once

#include "rtc.h"
#include <FreeRTOS.h>
#include <task.h>

/**
 * @brief second in ms
 */
#define SEC 1000

extern Time currentTime;
/**
 * @brief UartTask for freeRTOS
 * it sends data for uart every specefied time
 */
void vSend_UART_task(void* args);

/**
 * @brief Task to send time struct formatted by uart every speciefied time
 */
void vSend_time_uart_task(void* args);

/**
 * @brief Task to Read DS3231 data and time, storage all on a time struct, all every speciefied time
 */
void vRead_RTC_Time_task(void* pvParameters);

void vDraw_DISPLAY_task(void* pvParameters);
