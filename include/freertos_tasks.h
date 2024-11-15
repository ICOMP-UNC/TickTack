#pragma once

#include <FreeRTOS.h>
#include <task.h>

/**
 * @brief second in ms
 */
#define SEC 1000

/**
 * @brief UartTask for freeRTOS
 * it sends data for uart every specefied time
 */
void vSend_UART_task(void* args);