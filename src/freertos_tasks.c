#include "freertos_tasks.h"

#include "delay.h"
#include "display.h"
#include "exti_cfg.h"
#include "pwm.h"
#include "uart.h"
Time currentTime;
TaskHandle_t Handle_draw_display = NULL;
TaskHandle_t Handle_read_rtc = NULL;
TaskHandle_t Handle_alarm = NULL;
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
    // DS323_write_command(0x0E, 0b00011110);

    DS3231_Set_Alarm2(10, 26);
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
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait for a lecture notification
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {

            MAX7219_TIME(&currentTime);
            xSemaphoreGive(xSemaphore);
        }
        // vTaskDelay(pdMS_TO_TICKS(SEC)); // not neccesary with synchronization
    }
}

void vAlarm_task(void* pvParameters)
{
    (void)pvParameters;
    vTaskSuspend(NULL); // suspend himself
    uint16_t melody[] = {D4, F4,  A4, Ab4, F4, D4, D4,  F4, A4, Bb4, A4, Ab4, F4, D4, G4, Bb4, D5,
                         C5, Bb4, G4, D4,  F4, A4, Ab4, F4, D4, Bb4, A4, Ab4, G4, F4, G4, F4,  D4};

    uint16_t durations[] = {440, 200, 960, 420, 200, 830, 430, 220, 360, 200, 400,  420, 200, 910, 380, 200, 1000,
                            350, 200, 930, 390, 210, 870, 330, 220, 520, 360, 1530, 180, 380, 180, 370, 450, 1};
    while (true)
    {
        // melody length
        size_t length = sizeof(melody) / sizeof(melody[0]);

        for (size_t i = 0; i < length; i++)
        {
            // make sound
            start_buzzer(melody[i]);
            // note duration
            vTaskDelay(pdMS_TO_TICKS(durations[i]));
        }
        // Pausa entre repeticiones de la canción
        vTaskDelay(pdMS_TO_TICKS(SEC * 2)); // 2 segundos
    }
}

void semaphore_init()
{
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
}

// eint ISRs

// activate /desactivate alarm isr
void exti15_10_isr()
{
    if (exti_get_flag_status(EXTI10))
    {
        exti_reset_request(EXTI10);
        vTaskSuspend(Handle_read_rtc);

        usart_send_blocking(UART, 'I');

        vTaskResume(Handle_alarm);
    }
    else
    {
        exti_reset_request(EXTI12);

        vTaskSuspend(Handle_alarm);
        stop_buzzer();
        usart_send_blocking(UART, 'I');
        vTaskResume(Handle_read_rtc);
    }

    // give cpu time to tasks
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Handle_draw_display, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
