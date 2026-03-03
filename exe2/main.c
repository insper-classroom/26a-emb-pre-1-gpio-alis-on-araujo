#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_B = 7;
const int BTN_PIN_G = 26;

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_B);
  gpio_set_dir(BTN_PIN_B, GPIO_IN);
  gpio_pull_up(BTN_PIN_B);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  while (true) {
    if (!gpio_get(BTN_PIN_B)) {
      printf("Botao 1\n");
      while (!gpio_get(BTN_PIN_B)) {
      }
    }

    if (!gpio_get(BTN_PIN_G)) {
      printf("Botao 2\n");
      while (!gpio_get(BTN_PIN_G)) {
      }
    }
  }
}