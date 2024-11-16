
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

#define I2C_PORT GPIOB
#define I2C_SDA_PIN GPIO7
#define I2C_SCL_PIN GPIO6
#define I2C_CR2_FREQ 36 // Mhz

void configure_i2c(void);
