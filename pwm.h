#ifndef PWM_H
#define PWM_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

void pwm_init(uint gpio, float clkdiv, uint wrap);
void pwm_set_pulse_width(uint gpio, float pulse_width_us);

#endif // PWM_H