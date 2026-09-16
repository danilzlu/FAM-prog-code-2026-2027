#include <stdio.h>

int factorial(int n);

int main(void) {

    printf("%d\n", factorial(2));

    return 0;
}

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) {
     res *= i;
    }
    return res;
}