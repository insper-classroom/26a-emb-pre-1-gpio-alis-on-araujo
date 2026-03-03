#include <stdio.h>

#define NUM_ELEMENTS 5

int multiplyNumbers(int x, int y) {
    int product = x * y;
    return product;
}

int main(void) {
    int a = 2;
    int b = 5;
    int result = multiplyNumbers(a, b);
    printf("Result: %d\n", result);

    int arr[NUM_ELEMENTS];
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        arr[i] = i;
    }

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}