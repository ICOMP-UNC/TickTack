#include "exti_cfg.h"
#include "uart.h"
void configure_exti()
{

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_AFIO);
    rcc_periph_clock_enable(RCC_GPIOC);

    gpio_set_mode(RTC_INT_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, RTC_INT_PIN);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    // Enable EXTI12 interrupt in the NVIC
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);

    // Configure EXTI0 (PA0) for falling edge initially
    exti_select_source(EXTI10, RTC_INT_PORT);       // Set PA0 as the EXTI0 source
    exti_set_trigger(EXTI10, EXTI_TRIGGER_FALLING); // Trigger interrupt on falling edge
    exti_enable_request(EXTI10);
}
