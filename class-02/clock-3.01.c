/*
 * Пример решения задачи «Электронные часы — III».
 *
 * Программа считывает время в формате hh:mm:ss
 * и количество секунд n из следующей строки.
 * и выводит время в формате hh:mm:ss,
 * которое покажут часы через n секунд.
 */

#include <stdio.h>
#include <stdlib.h>

const int seconds_in_minute = 60;
const int seconds_in_hour = 3600;

int main(void) {

    int the_seconds_that_have_passed;
    int hours1, minutes1, seconds1;

    // Приглашение к вводу для пользователя (убрать для контеста)
    printf("Enter time as hh:mm:ss here: ");
    // В переменную res запишется количество удачно считанных чисел
    int res = scanf("%d:%d:%d", &hours1, &minutes1, &seconds1);
    // Если не удалось считать три числа,
    if (res != 3) {
        // то произошла ошибка, о чём сообщим,
        printf("Wrong time format!!!\n");
        // и программа завершится
        abort();
    }

    // Приглашение к вводу секунд и проверка ввода.
    printf("Enter seconds passed: ");
    res = scanf("%d", &the_seconds_that_have_passed);
    if (res != 1) {
        printf("Wrong number format!!!\n");
        abort();
    }

    // Вычисляем ответ аналогично сложению столбиком
    int hours2 = (the_seconds_that_have_passed / seconds_in_hour);
    int minutes2 = ((the_seconds_that_have_passed - hours2 * seconds_in_hour) / seconds_in_minute);
    int seconds2 =
        the_seconds_that_have_passed - hours2 * seconds_in_hour - minutes2 * seconds_in_minute;

    int seconds3 = (seconds1 + seconds2) % seconds_in_minute;
    int minutes3 = (minutes1 + minutes2 + (seconds1 + seconds2) / seconds_in_minute) % 60;
    int hours3 =
        (hours2 + hours1 + (minutes1 + minutes2 + (seconds1 + seconds2) / seconds_in_minute) / 60) %
        24;

    // Печатаем ответ, поясняя, что напечатано
    printf("Now time is %d:%d:%d", hours3, minutes3, seconds3);
    return 0;
}