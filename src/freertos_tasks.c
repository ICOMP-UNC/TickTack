#include "freertos_tasks.h"

#include "uart.h"

Time currentTime;

void vSend_UART_task(void* pvParameters)
{
    (void)pvParameters;
    while (true)
    {
        usart_send_blocking(USART1, dato);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vSend_time_uart_task(void* pvParameters)
{
    (void)pvParameters;
    // DS3231_Set_Date_Time(16,11,24,6,3,39,0); this line is for configurate DS3231, it shouldnt be use
    while (true)
    {
        send_time_uart(&currentTime);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vRead_RTC_Time(void* pvParameters)
{
    (void)pvParameters;

    while (true)
    {
        DS3231_Get_DateTime(&currentTime);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}
