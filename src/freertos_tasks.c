#include "freertos_tasks.h"
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