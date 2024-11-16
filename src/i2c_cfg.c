#include "i2c_cfg.h"

void configure_i2c()
{

    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_I2C1);

    gpio_set_mode(I2C_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, I2C_SCL_PIN | I2C_SDA_PIN);

    i2c_peripheral_disable(I2C1);
    i2c_set_standard_mode(I2C1);           // standard mode 100khz
    i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ);
    i2c_set_trise(I2C1, I2C_CR2_FREQ + 1); // Trise = Freq + 1 en modo estándar
    i2c_set_ccr(I2C1, 180);                // set clock control register to 180khz
    i2c_peripheral_enable(I2C1);           /** Enable I2C1 */
}
