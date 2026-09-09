/*
 * Пример решения задачи «Электронные часы — III».
 *
 * Программа считывает время в формате hh:mm:ss
 * и количество секунд n из следующей строки.
 * и выводит время в формате hh:mm:ss,
 * которое покажут часы через n секунд.
 */

#include <stdio.h>
#include <stdlib.h> // подключаем макрос abort()

int main(void) {
    int hours, minutes, seconds;
    int delta_seconds;

    // Приглашение к вводу для пользователя (убрать для контеста)
    printf("Enter time as hh:mm:ss: ");
    // В переменную res запишется количество удачно считанных чисел
    int res = scanf("%d:%d:%d", &hours, &minutes, &seconds);
    if (res != 3) {
        // то произошла ошибка, о чём сообщим,
        printf("Wrong time format!!!\n");
        // и программа завершится
        abort();
    }

    // Приглашение к вводу секунд и проверка ввода.
    printf("Enter seconds passed: ");
    res = scanf("%d", &delta_seconds);
    if (res != 1) {
        printf("Wrong number or not a number!\n");
        abort();
    }

    // Вычисляем ответ аналогично сложению столбиком
    hours = hours + (delta_seconds / 3600);
    delta_seconds = delta_seconds % 3600;
    minutes = minutes + (delta_seconds / 60);

    delta_seconds = delta_seconds % 60;
    seconds = seconds + delta_seconds;
    minutes += seconds / 60;
    seconds = seconds % 60;
    hours += minutes / 60;
    minutes %= 60;
    hours = hours % 60;

    // Печатаем ответ, поясняя, что напечатано
    printf("Now time is: %d:%d:%d", hours, minutes, seconds);
    return 0;
}