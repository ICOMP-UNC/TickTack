#include "pwm.h"

void configure_pwm(void)
{
    // Habilitar los relojes necesarios
    rcc_periph_clock_enable(RCC_GPIOA); // enable GPIOA clock
    rcc_periph_clock_enable(RCC_TIM1);  // enable  clock for TIM

    // Configurar el pin A9 como función alternativa (PWM)
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);

    // TIM1 configuration with
    // intern clock, edge activating and rising edge
    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    // Set PWM frequency
    uint32_t timer_clk = rcc_apb2_frequency;        // Reloj del temporizador (72 MHz)
    uint32_t prescaler = (timer_clk / 1000000) - 1; // Prescaler for 1 MHz 72000000 / 10000000 = 72 -1  = 71
    uint32_t period = 0; // initial period 0 (buzzer will sound only when alarm will be triggered)

    // setting values
    timer_set_prescaler(TIM1, prescaler);
    timer_set_period(TIM1, period);

    // Configurar el canal 2 (A9) en modo PWM
    timer_enable_oc_output(TIM1, TIM_OC2);          // set Match2 for timer 1
    timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1); // set m2 t1 as pwm
    timer_set_oc_value(TIM1, TIM_OC2, period / 2);  // 50% duty cycle

    // Habilitar salida principal y el temporizador
    timer_enable_break_main_output(TIM1);
    timer_enable_counter(TIM1);
}

// Set pwm frequency
void pwm_set_frequency(uint32_t frequency)
{
    uint32_t period = 1000000 / frequency;
    if (frequency == 0)
    {
        period = 0;
    }
    else
    {
        period = 1000000 / frequency;              // period in microseconds (for 1 MHz clock)
    }
    timer_set_period(TIM1, period);                // Establecer el periodo en el timer 2
    timer_set_oc_value(TIM1, TIM_OC2, period / 2); // 50% duty cycle (sonido cuadrado)
}
void start_buzzer(uint32_t frequency)
{
    pwm_set_frequency(frequency);
    timer_enable_counter(TIM1); // Habilitar el temporizador
}

void stop_buzzer()
{
    pwm_set_frequency(0);
    timer_disable_counter(TIM1); // Deshabilitar el temporizador
}

// Reproducir una nota por un tiempo específico (en milisegundos)
void play_note(uint32_t frequency, uint32_t duration)
{
    pwm_set_frequency(frequency); // Establecer la frecuencia de la nota
    delay_micro(duration);
    pwm_set_frequency(0);         // Apagar el sonido después de la duración
}
