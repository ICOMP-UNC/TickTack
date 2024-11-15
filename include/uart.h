#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#define UART_PORT GPIOA
#define UART_TX_PIN GPIO9
#define UART_RX_PIN GPIO10
#define UART_BAUDRATE 9600
#define UART_DATABITS 8

extern char dato;

void configure_usart(void);
