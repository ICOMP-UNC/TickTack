#include "uart.h"

char dato = 'd';

void configure_usart(void)
{

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);

    gpio_set_mode(UART_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, UART_TX_PIN | UART_RX_PIN);

    usart_set_baudrate(USART1, UART_BAUDRATE);
    usart_set_databits(USART1, UART_DATABITS);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

    usart_enable(USART1);
}
