#pragma once

#include "rtc.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
/**
 * @brief UART peripherial in use
 */
#define UART USART2
/**
 * @brief stm32 port using for uart configuration
 */
#define UART_PORT GPIOA
/**
 * @brief pin used for TX in uart1
 */
#define UART_TX_PIN GPIO2
/**
 * @brief pin used for RX in uart1
 */
#define UART_RX_PIN GPIO3
/**
 * @brief uart baurate configuration
 */
#define UART_BAUDRATE 9600
/**
 * @brief uart databits
 */
#define UART_DATABITS 8

/**
 * @brief uart buffersize for time struct transfer
 */
#define UART_BUFFER_SIZE 64
/**
 * @brief variable to transmit, it maybe change in the future
 */
extern char dato;

/**
 * @brief setup usart configurations
 * gpio clock and uart pheripherial configuration for uart transmitions
 */
void configure_usart(void);

/**
 * @brief send struct data formated by uart
 * @param time Time type struct
 */
void send_time_uart(const Time* time);
