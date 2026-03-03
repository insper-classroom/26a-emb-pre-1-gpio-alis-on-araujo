#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define LED_RED 4
#define LED_GREEN 6
#define BTN_RED 28
#define BTN_GREEN 26

int main() {
  stdio_init_all();

  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);
  gpio_put(LED_RED, 0);

  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_put(LED_GREEN, 0);

  gpio_init(BTN_RED);
  gpio_set_dir(BTN_RED, GPIO_IN);
  gpio_pull_up(BTN_RED);

  gpio_init(BTN_GREEN);
  gpio_set_dir(BTN_GREEN, GPIO_IN);
  gpio_pull_up(BTN_GREEN);

  bool led_red_state = false;
  bool led_green_state = false;

  while (true) {
    if (!gpio_get(BTN_RED)) {
      led_red_state = !led_red_state;
      gpio_put(LED_RED, led_red_state);
      while (!gpio_get(BTN_RED)) {
      }
    }

    if (!gpio_get(BTN_GREEN)) {
      led_green_state = !led_green_state;
      gpio_put(LED_GREEN, led_green_state);
      while (!gpio_get(BTN_GREEN)) {
      }
    }
  }
}