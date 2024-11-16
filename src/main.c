#include "display.h"
#include "freertos_tasks.h"
#include "i2c_cfg.h"
#include "rtc.h"
#include "spi_config.h"
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
    configure_usart();
    configure_i2c();
    configure_spi();
    MAX7219_Init(4);
    xTaskCreate(vSend_UART_task, "Send_Uart", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(vSend_time_uart_task, "Send_Time", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 2, NULL);
    xTaskCreate(vRead_RTC_Time_task, "ReadRTC", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 2, NULL);
    xTaskCreate(vDraw_DISPLAY_task, "DrawDisplay", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES - 2, NULL);

    vTaskStartScheduler();
    while (1)
    {
        /* Should never reach here */
    }
    return 0;
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
