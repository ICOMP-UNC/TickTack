#pragma once

#include "rtc.h"
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

/**
 * @brief second in ms
 */
#define SEC 1000

/**
 * @brief Handle to draw display task
 * Is used to control the signals to draw display task
 */
extern TaskHandle_t Handle_draw_display;
/**
 * @brief Handle to rtc read task
 * Is used to control the signals to rtc read task
 */
extern TaskHandle_t Handle_read_rtc;
/**
 * @brief Current time struct
 * This struct store all data time taked form DS3231
 */
extern Time currentTime;
/**
 * @brief Binary Semaphore
 * Used for protect currentTime variable to read and write actions
 */
extern SemaphoreHandle_t xSemaphore;
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
 * it syncrhonized with draw Display task
 */
void vRead_RTC_Time_task(void* pvParameters);
/**
 * @brief Task to write current Time in MAX7219 display
 * it syncrhonized with RTC time task
 */
void vDraw_DISPLAY_task(void* pvParameters);
/**
 * @brief Init binary semaphore
 */
void semaphore_init(void);
