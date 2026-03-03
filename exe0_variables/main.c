#include <stdio.h>
#include <stdbool.h>

static int foo(int value) {
    return value + 1;
}

int main(void) {
    int a = 0;
    bool b = false;

    while (1) {
        a = foo(a);

        if (a > 5) {
            b = true;
        }
    }

    return 0;
}