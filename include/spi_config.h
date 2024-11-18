#pragma once
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

/**
 * @brief SPI port used
 */
#define SPI_PORT GPIOA
/**
 * @brief NSS PIN
 * Controled manually as gpio
 */
#define SPI_NSS_PIN GPIO4
/**
 * @brief SPI SCK PIN
 */
#define SPI_SCK_PIN GPIO5
/**
 * @brief MISO SPI PIN
 * is not used but maybe will be neccesary
 */
#define SPI_MISO_PIN GPIO6
/**
 * @brief SPI MOSI PIN
 * Used to SEND data to MAX7219 display
 */
#define SPI_MOSI_PIN GPIO7
/**
 * @brief SPI BAUDARE preescale value
 */
#define SPI_BAUD_PRESC_VALUE 64
/**
 * @brief init spi
 */
void configure_spi(void);
