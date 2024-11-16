#pragma once
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

#define SPI_PORT GPIOB
#define SPI_NSS_PIN GPIO12
#define SPI_SCK_PIN GPIO13
#define SPI_MISO_PIN GPIO14
#define SPI_MOSI_PIN GPIO15
#define SPI_BAUD_PRESC_VALUE 4

void configure_spi(void);
