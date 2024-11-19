#include "battery.h"
#include "delay.h"
// Variable para almacenar el valor del ADC
volatile uint16_t bat_value = 0;
// Configuración del ADC
void configure_adc(void)
{
    // Habilitar relojes
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_ADC1);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO1);

    adc_power_off(ADC1);
    adc_enable_scan_mode(ADC1);
    adc_set_single_conversion_mode(ADC1);

    adc_set_sample_time(ADC1, ADC_CHANNEL9, ADC_SMPR_SMP_239DOT5CYC);
    uint8_t channel_array[] = {ADC_CHANNEL9};
    adc_set_regular_sequence(ADC1, 1, channel_array);

    adc_enable_dma(ADC1);
    adc_power_on(ADC1);
    adc_reset_calibration(ADC1);
    adc_calibrate(ADC1);

    adc_start_conversion_direct(ADC1);

    adc_enable_eoc_interrupt(ADC1);
    nvic_enable_irq(NVIC_ADC1_2_IRQ);
}

// Configuración del DMA

// Configuración del Timer 3
void configure_timer3(void)
{

    /* Habilitar reloj para TIM3 */
    rcc_periph_clock_enable(RCC_TIM3);

    /* Configurar el Timer 3 */
    // timer_reset(TIM3);
    timer_set_prescaler(TIM3, 7200 - 1); // Prescaler para que el timer corra a 10 kHz
    timer_set_period(TIM3, 1000 - 1);    // Periodo para 10 Hz (cada 100 ms)

    /* Configurar TRGO para disparar en coincidencia (update event) */
    timer_enable_compare_control_update_on_trigger(TIM3);
    timer_set_master_mode(TIM3, TIM_CR2_MMS_ENABLE);

    timer_enable_counter(TIM3); // Habilitar contador
}

void configure_battery_leds()
{
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO3 | GPIO4 | GPIO5);

    // Inicializar los pines en estado apagado
    gpio_clear(GPIOB, GPIO3 | GPIO4 | GPIO5);
}
