#include "exti_cfg.h"
#include "uart.h"
void configure_exti()
{
    // configure RTC ALARM EINT PA10
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(RTC_INT_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, RTC_INT_PIN); // pin cfg
    gpio_set(RTC_INT_PORT, RTC_INT_PIN);                                                   // pullup established

    nvic_enable_irq(NVIC_EXTI15_10_IRQ); // Enable EXTI12 interrupt in the NVIC

    // Configure EXTI10 (PA10) for falling edge initially
    exti_select_source(EXTI10, RTC_INT_PORT);       // Set PA10 as the EXTI10 source
    exti_set_trigger(EXTI10, EXTI_TRIGGER_FALLING); // Trigger interrupt on falling edge
    exti_enable_request(EXTI10);

    // configure DESACTIVATE ALARM EINT PB12
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(BUTTON_OFFALARM_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, BUTTON_OFFALARM_PIN);
    gpio_set(BUTTON_OFFALARM_PORT, BUTTON_OFFALARM_PIN);

    // Configure EXTI10 (PB12) for falling edge initially
    exti_select_source(EXTI12, BUTTON_OFFALARM_PORT); // Set PA0 as the EXTI0 source
    exti_set_trigger(EXTI12, EXTI_TRIGGER_FALLING);   // Trigger interrupt on falling edge
    exti_enable_request(EXTI12);
}
