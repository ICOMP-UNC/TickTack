#include "spi_config.h"

void configure_spi(void)
{
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, SPI_NSS_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_SCK_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_MISO_PIN);
    gpio_set_mode(SPI_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SPI_MOSI_PIN);

    spi_clean_disable(SPI2);
    spi_enable(SPI2);
    spi_set_master_mode(SPI2);
    spi_set_bidirectional_mode(SPI2);
    spi_set_clock_polarity_0(SPI2);
    spi_set_clock_phase_0(SPI2);
    spi_set_baudrate_prescaler(SPI2, SPI_BAUD_PRESC_VALUE);
    spi_send_msb_first(SPI2);
    spi_disable_crc(SPI2);
}
