#include "uart.h"

char dato = 'd';

void configure_usart(void)
{

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

    gpio_set_mode(UART_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, UART_TX_PIN | UART_RX_PIN);

    usart_set_baudrate(USART2, UART_BAUDRATE);
    usart_set_databits(USART2, UART_DATABITS);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

void send_time_uart(const Time* time)
{
    char buffer[UART_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Date: %02d/%02d/%02d Time: %02d:%02d:%02d\n", time->day, time->month, time->year,
             time->hour, time->minute, time->second);
    for (char* p = buffer; *p != '\0'; p++)
    {
        usart_send_blocking(UART, *p);
    }
}
