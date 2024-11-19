#include "display.h"
#include "exti_cfg.h"
#include "freertos_tasks.h"
#include "i2c_cfg.h"
#include "pwm.h"
#include "rtc.h"
#include "spi_config.h"
#include "timer_cfg.h"
#include "uart.h"
/**
 * @brief Configure the system clock to run at 72 MHz using an 8 MHz external crystal.
 */
void systemInit(void);

void systemInit(void)
{
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
}

/**
 * @brief Main entry point of the program.
 */
int main(void)
{
    systemInit();
    semaphore_init();
    configure_usart();
    configure_i2c();
    configure_spi();
    configure_exti();
    configure_timer();
    configure_pwm();
    MAX7219_Init(0);
    xTaskCreate(vSend_UART_task, "Send_Uart", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 4, NULL);
    xTaskCreate(vSend_time_uart_task, "Send_Time", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 4, NULL);
    xTaskCreate(vRead_RTC_Time_task, "ReadRTC", configMINIMAL_STACK_SIZE + 100, NULL, configMAX_PRIORITIES,
                &Handle_read_rtc);
    xTaskCreate(vDraw_DISPLAY_task, "DrawDisplay", configMINIMAL_STACK_SIZE + 100, NULL, configMAX_PRIORITIES,
                &Handle_draw_display);

    vTaskStartScheduler();
    while (1)
    {
        /* Should never reach here */
    }
    return 0;
}
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

void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    /* This function is called if a stack overflow is detected. */
    (void)xTask;
    (void)pcTaskName;

    /* Optionally log the error or take corrective action here */
    /* For now, we will just enter an infinite loop to halt the system */
    for (;;)
        ;
}
