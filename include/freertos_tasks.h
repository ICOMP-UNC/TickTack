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
 * @brief Handle Alarm task
 * Is used to control the signals from isr to alarm task
 */
extern TaskHandle_t Handle_alarm;
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

extern TaskHandle_t Handle_battery;
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
 * it syncrhonize with draw Display task
 */
void vRead_RTC_Time_task(void* pvParameters);
/**
 * @brief Task to write current Time in MAX7219 display
 * it syncrhonize with RTC time task
 */
void vDraw_DISPLAY_task(void* pvParameters);
/**
 * @brief Task to make sound the melody in buzzer
 */
void vAlarm_task(void* pvParameters);

void vBattery_task(void* pvParameters);
/**
 * @brief Init binary semaphore
 */
void semaphore_init(void);

void send_bat_value_over_uart(int bat_value1);
