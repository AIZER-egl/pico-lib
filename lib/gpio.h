// Library for Raspberry pico GPIO 1.0.0 by @IkerCs / @aizer-egl
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3
#define OUTPUT_PWM 4
#define HIGH 1
#define LOW 0
#define BUILTIN_LED 25

void pinMode(uint8_t pin, uint8_t mode);

void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);

void analogWrite(uint8_t pin, uint8_t value);
uint16_t analogRead(uint8_t pin);

void pinMode(uint8_t pin, uint8_t mode) {
    switch (mode) {
        case INPUT:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            break;
        case OUTPUT:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_OUT);
            break;
        case INPUT_PULLUP:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            gpio_pull_up(pin);
            break;
        case INPUT_PULLDOWN:
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            gpio_pull_down(pin);
            break;
        case OUTPUT_PWM:
            gpio_set_function(pin, GPIO_FUNC_PWM);
            break;
    }
}

void digitalWrite(uint8_t pin, uint8_t value) {
    gpio_put(pin, value);
}

uint8_t digitalRead(uint8_t pin) {
    return gpio_get(pin);
}

void analogWrite(uint8_t pin, uint8_t value) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 255);
    pwm_set_chan_level(slice_num, PWM_CHAN_A + (pin % 2), value);
    pwm_set_enabled(slice_num, true);
}

uint16_t analogRead(uint8_t pin) {
    adc_init();
    adc_gpio_init(pin);
    adc_select_input(pin);
    return adc_read();
};