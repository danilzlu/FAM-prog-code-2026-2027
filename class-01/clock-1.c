/*
 * Пример решения задачи «Электронные часы — I».
 *
 * Программа считывает время в формате hh:mm:ss
 * и выводит количество секунд с начала суток.
 */

#include <stdio.h>

// Это глобальные переменные, они доступны из любого места в этом файле
// const перед int --- это указание компилятору, что изменять значение этой переменной в программе
// нельзя
const int seconds_in_minute = 60;
const int seconds_in_hour = 3600;

int main(void) {
    int hours, minutes, seconds;

    // Читаем данные, учитывая формат ввода, указанные в задании
    scanf("%d:%d:%d", &hours, &minutes, &seconds);

    // Вычисляем результат используя константы (избегаем магических значений)
    int result = hours * seconds_in_hour + minutes * seconds_in_minute + seconds;

    printf("%d", result);

    return 0;
}