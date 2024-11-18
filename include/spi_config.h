#pragma once
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

#define SPI_PORT GPIOA
#define SPI_NSS_PIN GPIO4
#define SPI_SCK_PIN GPIO5
#define SPI_MISO_PIN GPIO6
#define SPI_MOSI_PIN GPIO7
#define SPI_BAUD_PRESC_VALUE 64

void configure_spi(void);
