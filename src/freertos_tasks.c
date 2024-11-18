#include "freertos_tasks.h"

#include "display.h"
#include "uart.h"

Time currentTime;
TaskHandle_t Handle_draw_display = NULL;
TaskHandle_t Handle_read_rtc = NULL;
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
    // DS3231_Set_Date_Time(17, 11, 24, 7, 19, 32, 30);
    // this line is for configurate DS3231, it shouldnt be use
    while (true)
    {
        DS3231_Get_DateTime(&currentTime);
        // usart_send_blocking(UART, 'l');
        xTaskNotifyGive(Handle_draw_display);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vDraw_DISPLAY_task(void* pvParameters)
{
    (void)pvParameters;
    while (true)
    {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        MAX7219_TIME(&currentTime);
        // vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}
