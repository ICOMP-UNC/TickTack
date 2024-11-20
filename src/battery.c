#include "battery.h"
#include "delay.h"
// Variable para almacenar el valor del ADC
volatile uint16_t bat_value = 0;
// Configuración del ADC
void configure_adc(void)
{
    // Habilitar relojes
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_ADC1);
    rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV6);
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO0);

    adc_power_off(ADC1);
    adc_disable_scan_mode(ADC1);
    adc_set_continuous_conversion_mode(ADC1); // Habilitar modo continuo
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_55DOT5CYC);
    adc_set_regular_sequence(ADC1, 1, ADC_CHANNEL1);
    adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_TIM3_TRGO); // Configurar el trigger externo
    adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTTRIG);          // Habilitar el trigger externo
    adc_power_on(ADC1);
    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);
}
// Configuración del DMA
void configure_dma(void)
{
    rcc_periph_clock_enable(RCC_DMA1);
    dma_channel_reset(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t)&ADC_DR(ADC1));
    dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t)&bat_value);
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, 1);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
    dma_enable_channel(DMA1, DMA_CHANNEL1);
    nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
}
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
    timer_set_master_mode(TIM3, TIM_CR2_MMS_UPDATE);

    timer_enable_counter(TIM3); // Habilitar contador
}

void configure_battery_leds()
{
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    // Inicializar los pines en estado apagado
    gpio_set(GPIOB, GPIO13);
}
