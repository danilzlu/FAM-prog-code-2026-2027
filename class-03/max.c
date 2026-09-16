/*
 * Пример решения задачи <<МАХ>>
 */

#include <stdio.h>

// объявление функции
int max(int a, int b);

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        // вызываем max(a, b) внутри printf, 
        // значение передастся в 4ый аргумент printf
        printf("max(%d, %d) = %d\n", a, b, max(a,b));
    }

    return 0;
}

// определение функции max
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}