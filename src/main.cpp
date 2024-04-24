#include "pico/stdlib.h"
#include "stdio.h"

#include "pico_explorer.hpp"
#include "button.hpp"
#include "analog.hpp"
#include "encoder.hpp"
#include "motor.hpp"
#include "pid.hpp"
#include "ws2812.hpp"

#define COUNTS_PER_REV 1496

using namespace pimoroni;
using namespace motor;
using namespace encoder;
using namespace plasma;

const uint UPDATES = 100;
constexpr float UPDATE_RATE = 1.0f / (float)UPDATES;

Button button_a(PicoExplorer::A);
Button button_b(PicoExplorer::B);

Motor motor_A(PicoExplorer::MOTOR2_PINS);

WS2812 rgb_led(1, pio0, 0, 23);

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    stdio_init_all();
    rgb_led.start(UPDATES);
    motor_A.init();
    uint8_t red_value = 0;
    uint8_t green_value = 0;
    float motor_speed = 0.0f;
    while (true) {

        printf("Hello! \n");
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        if(button_a.read()) {
            motor_speed += 0.05;
            
        }
        if(button_b.read()) {
            motor_speed -= 0.05;
        }
        red_value = motor_speed < 0 ? abs(motor_speed) * 255 : 0;
        green_value = motor_speed >= 0 ? abs(motor_speed) * 255 : 0;
        rgb_led.set_rgb(0, red_value, green_value, 0);
        motor_A.speed(motor_speed);
        sleep_ms(10);
        // sleep_ms(300);
        // gpio_put(PICO_DEFAULT_LED_PIN, false);
        // sleep_ms(300);
    }
}