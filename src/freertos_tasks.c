#include "freertos_tasks.h"
#include "rtc.h"
#include "uart.h"

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
    Time currentTime;

    while (true)
    {
        // DS3231_Get_DateTime(&currentTime);
        send_time_uart(&currentTime);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}
