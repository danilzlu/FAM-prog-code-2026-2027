/*
 * Пример решения задачи <<Разворот>>.
 */

#include <stdio.h>

int main(void) {

    int n;
    scanf("%d", &n);

    // VLA == Variable Length Array == массив переменной длины;
    // его размер станет известен во время выполнения
    // и не сможет измениться
    int array[n];

    // читаем массив со стандартного ввода (stdin) поэлементно
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    // печатаем массив на стандартный вывод В ОБРАТНОМ ПОРЯДКЕ (stdout)
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }

    return 0;
}