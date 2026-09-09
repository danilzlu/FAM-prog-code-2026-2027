/*
 * Пример решения задачи «Цифры 2».
 *
 * Программа считывает число number
 * и выводит количество цифр этого числа.
 * 
 * ISSUES:
 * - Wrong answer when number == 0:
 *   expected 1, got 0.
 */

#include <stdio.h>

int main(void) {

    int number;
    scanf("%d", &number);

    // Вводим переменную, с помощью которой будем пересчитывать цифры
    int count = 0;


    while (number != 0) {     // кажется, с условием или всем циклом что-то не так
        number = number / 10; // деление нацело на 10 "съедает" последнюю цифру.
        count = count + 1;    // раз "съели" цифру, "загибаем палец"
    }

    // печатаем ответ
    printf("%d\n", count);

    return 0;
}