#include "freertos_tasks.h"

#include "display.h"
#include "uart.h"

Time currentTime;
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
    // DS3231_Set_Date_Time(16, 11, 24, 6, 14, 43, 0);
    //  this line is for configurate DS3231, it shouldnt be use
    while (true)
    {
        send_time_uart(&currentTime);
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vRead_RTC_Time_task(void* pvParameters)
{
    (void)pvParameters;

    while (true)
    {
        DS3231_Get_DateTime(&currentTime);
        usart_send_blocking(UART, 'l');
        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vDraw_DISPLAY_task(void* pvParameters)
{
    (void)pvParameters;
    int i = 0;
    while (true)
    {
        MAX7219_Write_Num('2', '4', 4);
        // MAX7219_Write_Num('2','3',4);
        MAX7219_Write_Tens('3', 2);

        // MAX7219_Write_Char( ':', 1);
        switch (i)
        {
        case 0:
            // MAX7219_Clear();
            MAX7219_Write_Units('1', 2);
            break;
        case 1:
            MAX7219_Write_Units('2', 2);
            break;
        case 2:
            MAX7219_Write_Units('3', 2);
            break;
        case 3:
            MAX7219_Write_Units('4', 2);
            break;
        case 4:
            MAX7219_Write_Units('5', 2);
            i = -1;
            break;
        default:
            break;
        }
        i++;

        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}
