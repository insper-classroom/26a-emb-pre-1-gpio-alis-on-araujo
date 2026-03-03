#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define LED_R 5
#define LED_P 8
#define LED_B 11
#define LED_Y 15
#define BTN 28

int main() {
  stdio_init_all();

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_put(LED_R, 0);

  gpio_init(LED_P);
  gpio_set_dir(LED_P, GPIO_OUT);
  gpio_put(LED_P, 0);

  gpio_init(LED_B);
  gpio_set_dir(LED_B, GPIO_OUT);
  gpio_put(LED_B, 0);

  gpio_init(LED_Y);
  gpio_set_dir(LED_Y, GPIO_OUT);
  gpio_put(LED_Y, 0);

  gpio_init(BTN);
  gpio_set_dir(BTN, GPIO_IN);
  gpio_pull_up(BTN);

  while (true) {
    if (!gpio_get(BTN)) {

      gpio_put(LED_R, 1);
      gpio_put(LED_P, 0);
      gpio_put(LED_B, 0);
      gpio_put(LED_Y, 0);
      sleep_ms(300);

      gpio_put(LED_R, 0);
      gpio_put(LED_P, 1);
      gpio_put(LED_B, 0);
      gpio_put(LED_Y, 0);
      sleep_ms(300);

      gpio_put(LED_R, 0);
      gpio_put(LED_P, 0);
      gpio_put(LED_B, 1);
      gpio_put(LED_Y, 0);
      sleep_ms(300);

      gpio_put(LED_R, 0);
      gpio_put(LED_P, 0);
      gpio_put(LED_B, 0);
      gpio_put(LED_Y, 1);
      sleep_ms(300);

      gpio_put(LED_Y, 0);

      while (!gpio_get(BTN)) {
      }
    }
  }
}