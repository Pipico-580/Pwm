#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define SERVO_GPIO 22  // Pino do servomotor
#define LED_GPIO 12     // Pino do LED RGB
#define PWM_FREQ 50     // Frequência do PWM (50Hz -> período de 20ms)

void set_servo_pulse(uint gpio, float pulse_width_us) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint wrap = pwm_get_counter(slice_num);
    uint16_t clkdiv = 64; // valor padrão, ajuste conforme necessário
    float ticks_per_us = (clock_get_hz(clk_sys) / clkdiv) / 1e6;
    uint level = (uint)(pulse_width_us * ticks_per_us);
    pwm_set_gpio_level(gpio, level);
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(LED_GPIO, GPIO_FUNC_PWM);
    
    uint slice_num = pwm_gpio_to_slice_num(SERVO_GPIO);
    pwm_set_clkdiv(slice_num, 64); // Divisor de clock
    pwm_set_wrap(slice_num, 20000);    // Define o período para 20ms (50Hz)
    pwm_set_enabled(slice_num, true);

    while (true) {
        // Posição 180 graus
        set_servo_pulse(SERVO_GPIO, 2400);
        sleep_ms(5000);
        
        // Posição 90 graus
        set_servo_pulse(SERVO_GPIO, 1470);
        sleep_ms(5000);
        
        // Posição 0 graus
        set_servo_pulse(SERVO_GPIO, 500);
        sleep_ms(5000);
        
        // Movimentação suave entre 0 e 180 graus
        for (int pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_pulse(SERVO_GPIO, pulse);
            sleep_ms(10);
        }
        for (int pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_pulse(SERVO_GPIO, pulse);
            sleep_ms(10);
        }
    }
}