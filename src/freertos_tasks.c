#include "freertos_tasks.h"

#include "delay.h"
#include "display.h"
#include "uart.h"

Time currentTime;
TaskHandle_t Handle_draw_display = NULL;
TaskHandle_t Handle_read_rtc = NULL;
SemaphoreHandle_t xSemaphore;
void vSend_UART_task(void* pvParameters)
{
    (void)pvParameters;
    while (true)
    {
        usart_send_blocking(UART, dato);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vSend_time_uart_task(void* pvParameters)
{
    (void)pvParameters;

    while (true)
    {
        send_time_uart(&currentTime);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vRead_RTC_Time_task(void* pvParameters)
{
    (void)pvParameters;
    // DS3231_Set_Date_Time(18, 11, 24, 1, 4, 19, 25);
    // this function must be commented unless you want to calibrate DS3231 Hour
    while (true)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            DS3231_Get_DateTime(&currentTime);
            xSemaphoreGive(xSemaphore);
        }
        xTaskNotifyGive(Handle_draw_display);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vDraw_DISPLAY_task(void* pvParameters)
{
    (void)pvParameters;
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Espera notificación de nueva lectura
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            delay_milli(1);
            MAX7219_TIME(&currentTime);
            xSemaphoreGive(xSemaphore);
        }
        // vTaskDelay(pdMS_TO_TICKS(SEC)); // No es necesario con la sincronización
    }
}
void semaphore_init()
{
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
}
