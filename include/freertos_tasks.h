#pragma once

#include <FreeRTOS.h>
#include <task.h>

#define SEC 1000

void vSend_UART_task(void* args);