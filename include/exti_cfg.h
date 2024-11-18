#pragma once
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define RTC_INT_PIN GPIO10
#define RTC_INT_PORT GPIOA

void configure_exti(void);
