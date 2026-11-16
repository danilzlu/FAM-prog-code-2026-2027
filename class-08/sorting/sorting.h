#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

/* Указатель на минимальный элемент или NULL при n == 0. */
int *min_element(int *a, size_t n);

/* Обмен значений двух целых чисел. */
void swap_int(int *x, int *y);

/* Сортировка выбором минимального элемента. */
void selection_sort(int *a, size_t n);

/* Вставляет value в отсортированный префикс a[0..sorted_count).
   Массив должен иметь место под a[sorted_count].
   Сдвигает большие элементы вправо. */
void insert_sorted_prefix(int *a, size_t sorted_count, int value);

/* Сортировка вставками через insert_sorted_prefix. */
void insertion_sort(int *a, size_t n);

#endif
