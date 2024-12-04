
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

/**
 * @brief I2C port used
 */
#define I2C_PORT GPIOB
/**
 * @brief I2C SDA pin
 */
#define I2C_SDA_PIN GPIO7
/**
 * @brief I2C SCL pin
 */
#define I2C_SCL_PIN GPIO6
/**
 * @brief I2C CR2 frequency
 */
#define I2C_CR2_FREQ 36 // Mhz

/**
 * @brief configure gpio mdoe and i2c to transfer data
 */
void configure_i2c(void);
