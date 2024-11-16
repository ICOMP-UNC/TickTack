#pragma once

#include <FreeRTOS.h>
#include <task.h>

#include "rtc.h"

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

void vSend_time_uart_task(void* args);

void vRead_RTC_Time(void* pvParameters);
