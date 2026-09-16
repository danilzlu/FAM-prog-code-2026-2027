/*
 * Примеры объявлений, определений функций и их использование.
 */

#include <stdio.h>

// объявление функции: factorial принимает один аргумент типа int и возвращает int
int factorial(int n);

// объявление функции: print_hello принимает один аргумент типа int и ничего не возвращает
void print_hello(int n);

// объявление вместе с определением функции: max принимает два аргумента типа int и возвращает int
int max(int x, int y) {
    return x > y ? x : y; // короткий способ вернуть максимум двух чисел
}


int main(void) {

    // вызов функции print_hello c n == 3
    print_hello(3);

    #if BUG
    // недопустимо, так как print_hello не имеет возвращаемого значения
    // CE --- ошибка во время компиляции
    int a = print_hello(3);
    #endif

    int number;
    scanf("%d", &number);

    // вызов функции factorial c n == number
    int result = factorial(number);

    #if NOBUG
    // допустимо: возвращаемое значение можно игнорировать
    factorial(number + 1);
    #endif

    printf("%d\n", result);

    return 0;
}

// определение функции:
int factorial(int n) {
    // тело функции:

    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }

    return res;
}

// определение функции:
void print_hello(int n) {

    // n раз печатаем `Hello, World!`
    for (int i = 0; i != n; ++i) {
        printf("Hello, World!\n");
    }
}


