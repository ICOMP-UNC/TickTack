#include "spi_config.h"

void configure_spi(void)
{
    rcc_periph_clock_enable(RCC_SPI2);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, SPI_NSS_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_SCK_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_MISO_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_MOSI_PIN);

    // spi_reset(SPI2);

    /* Set SPI2 to master mode. */
    spi_init_master(SPI2, SPI_CR1_BAUDRATE_FPCLK_DIV_32, SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, SPI_CR1_CPHA_CLK_TRANSITION_1,
                    SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);

    /* Set software slave management and NSS pin high. */
    // spi_enable_software_slave_management(SPI2);
    // spi_set_nss_high(SPI2);

    /* Enable SPI2. */
    spi_enable(SPI2);
}
