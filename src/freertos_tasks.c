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
    DS323_write_command(0x0E, 0b00011110);
    DS323_write_command(0x0F, 0b00001000);
    DS3231_Set_Alarm2(8, 50);
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

void vAlarm_task(void* pvParameters)
{
    (void)pvParameters;
    vTaskSuspend(NULL);                                      // suspend himself
    uint16_t melody[] = {D4, F4,  A4, Ab4, F4,  D4,          // Spider-Man, Spider-Man
                         D4, F4,  A4, Bb4, A4,  Ab4, F4, D4, // Does whatever a spider can
                         G4, Bb4, D5, C5,  Bb4, G4,  D4, F4, A4, Ab4, F4, D4, Bb4, A4, Ab4, G4, F4, G4, F4, D4};

    uint16_t durations[] = {
        440, 200, 960, 420, 170, 830, 430,                                // Duración de las primeras frases
        220, 360, 200, 400, 420, 200, 910, 380,  200, 1000, 350, 200, 930,
        390, 210, 870, 330, 220, 520, 360, 1530, 180, 380,  180, 370, 450 // Duración de la siguiente parte
    };
    while (true)
    {
        // Longitud de la melodía
        size_t length = sizeof(melody) / sizeof(melody[0]);

        for (size_t i = 0; i < length; i++)
        {
            if (melody[i] == 0)
            {
                // Si la nota es 0 (pausa), no emitimos sonido
                vTaskDelay(pdMS_TO_TICKS(durations[i]));
            }
            else
            {
                // Generar la nota
                start_buzzer(melody[i]);
                // Duración de la nota
                vTaskDelay(pdMS_TO_TICKS(durations[i]));
            }
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

// activate alarm isr
void exti15_10_isr()
{
    if (exti_get_flag_status(EXTI10))
    {
        exti_reset_request(EXTI10);
        vTaskSuspend(Handle_read_rtc);

        gpio_toggle(GPIOC, GPIO13);
        usart_send_blocking(UART, 'I');

        vTaskResume(Handle_alarm);
    }
    else
    {
        exti_reset_request(EXTI12);

        vTaskSuspend(Handle_alarm);
        stop_buzzer();
        gpio_toggle(GPIOC, GPIO13);
        usart_send_blocking(UART, 'I');
        vTaskResume(Handle_read_rtc);
    }

    // give cpu time to tasks
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Handle_draw_display, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
