/*
 * Пример решения задачи <<НОД>>
 *
 * ISSUES:
 *      - избыточный код: функция factorial для демонстрации рекурсивных вызовов
 *        а не для решения задачи
 *      - рекурсивная функция gcd(int a, int b) может работать неправильно для отрицательных аргументов
 */

#include <stdio.h>


int gcd(int a, int b);

int factorial(int n);

int main(void) {

    int a, b;
    scanf("%d%d", &a, &b);

    int result = gcd(a, b);

    printf("%d\n", result);

    return 0;
}

// рекурсивное определение функции factorial
int factorial(int n) {

    // factorial(0) == 1
    // рекурсия будет разворачиваться, пока n не станет равным 0
    if (n == 0) {
        return 1;
    }

    // по определению n! = n * (n - 1)!
    return n * factorial(n - 1);
}

int gcd(int a, int b) {
    
    // условие остановки алгоритма Евклида
    if (b == 0)
        return a;

    // шаг алгоритма Евклида
    return gcd(b, a % b);
}

