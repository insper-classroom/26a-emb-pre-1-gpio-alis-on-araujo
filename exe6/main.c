#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

static const int FIRST_GPIO = 2;
static const int BTN_PIN_G = 28;

static int cnt = 0;
static int last_btn = 1; /* botão com pull-up => não pressionado = 1 */

/* bit patterns for 7-seg (0-9) */
static const uint8_t bits[10] = {
    0x3f, /* 0 */
    0x06, /* 1 */
    0x5b, /* 2 */
    0x4f, /* 3 */
    0x66, /* 4 */
    0x6d, /* 5 */
    0x7d, /* 6 */
    0x07, /* 7 */
    0x7f, /* 8 */
    0x67  /* 9 */
};

static void seven_seg_init(void)
{
    for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; ++gpio) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }
}

static void seven_seg_display(void)
{
    /* garante que cnt está em 0..9 (defensivo, embora código mantenha isso) */
    int index = cnt;
    if (index < 0) index = 0;
    if (index > 9) index = 9;

    uint8_t value = bits[index];
    for (int i = 0; i < 7; ++i) {
        int gpio = FIRST_GPIO + i;
        int bit = (value >> i) & 1u;
        gpio_put(gpio, bit);
    }
}

int main(void)
{
    stdio_init_all();

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    seven_seg_init();
    seven_seg_display();

    while (true) {
        int btn = gpio_get(BTN_PIN_G);
        /* Detect falling edge: last_btn == 1 and btn == 0 */
        if (last_btn && !btn) {
            ++cnt;
            if (cnt > 9) {
                cnt = 0;
            }
            seven_seg_display();
            printf("cnt: %d\n", cnt);
        }
        last_btn = btn;
        sleep_ms(10);
    }

    return 0;
}