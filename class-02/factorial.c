#include <stdio.h>

int factorial(int n);

int main(void) {

    printf("%d\n", factorial(2));

    return 0;
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}