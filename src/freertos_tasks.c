#include "freertos_tasks.h"

#include "delay.h"
#include "display.h"
#include "exti_cfg.h"
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
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            // delay_milli(1);
            send_time_uart(&currentTime);
            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(SEC));
    }
}

void vRead_RTC_Time_task(void* pvParameters)
{
    (void)pvParameters;
    // DS3231_Set_Date_Time(18, 11, 24, 1, 00, 42, 00);
    //  this function must be commented unless you want to calibrate DS3231 Hour
    DS323_write_command(0x0E, 0b00011110);
    DS323_write_command(0x0F, 0b00001000);
    DS3231_Set_Alarm2(3, 43);
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
            // delay_milli(1);
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

// eint ISRs

// alarm isr
void exti15_10_isr()
{
    exti_reset_request(EXTI10);
    gpio_toggle(GPIOC, GPIO13);
    usart_send_blocking(UART, 'B');
    timer_set_period(TIM1, 1000000 / 1000);
    timer_set_oc_value(TIM1, TIM_OC2, (1000000 / 1000) / 2); // 50% de ciclo útil inicial
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Handle_draw_display, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
