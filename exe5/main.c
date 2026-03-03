#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define BTN_PIN1 26
#define BTN_PIN2 7

// debounce time in milliseconds
#define DEBOUNCE_MS 50

static inline uint32_t ms_now(void) {
    return (uint32_t)(time_us_64() / 1000ULL);
}

int main(void) {
    stdio_init_all();

    gpio_init(BTN_PIN1);
    gpio_set_dir(BTN_PIN1, GPIO_IN);
    gpio_pull_up(BTN_PIN1);

    gpio_init(BTN_PIN2);
    gpio_set_dir(BTN_PIN2, GPIO_IN);
    gpio_pull_up(BTN_PIN2);

    // states for button 1
    int last_read_1 = gpio_get(BTN_PIN1);
    int stable_state_1 = last_read_1;
    uint32_t last_change_time_1 = ms_now();
    int count1 = 0;

    // states for button 2
    int last_read_2 = gpio_get(BTN_PIN2);
    int stable_state_2 = last_read_2;
    uint32_t last_change_time_2 = ms_now();
    int count2 = 0;

    while (true) {
        uint32_t now = ms_now();

        // --- Button 1 ---
        int reading1 = gpio_get(BTN_PIN1);
        if (reading1 != last_read_1) {
            last_change_time_1 = now;
            last_read_1 = reading1;
        } else if ((now - last_change_time_1) > DEBOUNCE_MS) {
            if (stable_state_1 != reading1) {
                stable_state_1 = reading1;
                // stable_state == 0 means pressed (pull-up)
                if (stable_state_1 == 0) {
                    count1++;
                    printf("Botao 1: %d\n", count1);
                }
            }
        }

        // --- Button 2 ---
        int reading2 = gpio_get(BTN_PIN2);
        if (reading2 != last_read_2) {
            last_change_time_2 = now;
            last_read_2 = reading2;
        } else if ((now - last_change_time_2) > DEBOUNCE_MS) {
            if (stable_state_2 != reading2) {
                stable_state_2 = reading2;
                if (stable_state_2 == 0) {
                    count2++;
                    printf("Botao 2: %d\n", count2);
                }
            }
        }

        // small sleep to avoid busy-waiting
        sleep_ms(1);
    }

    return 0;
}