#include <stdio.h>
#include <stdbool.h>

static int foo(int value) {
    return value + 1;
}

int main(void) {
    int a = 0;

    while (1) {
        a = foo(a);

        if (a > 5) {
            bool b = true;
            if (b) break;
        }
    }

    return 0;
}