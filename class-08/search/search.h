#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>
#include <stddef.h>

/* Индекс первого совпадения или -1. */
ptrdiff_t linear_search_index(const int *a, size_t n, int target);

/* Указатель на первый найденный элемент или NULL. */
const int *linear_search_ptr(const int *a, size_t n, int target);

/* Аналог линейного поиска для произвольного типа.
   compare(x, y) возвращает 0, когда элементы равны.
   base указывает на массив из n элементов размером element_size байт.
   Результат указывает внутрь исходного массива; память освобождать нельзя. */
const void *linear_search_generic(const void *base, size_t n, size_t element_size, const void *key,
                                  int (*compare)(const void *, const void *));

/* Массив должен быть отсортирован по неубыванию. Индекс или -1. */
ptrdiff_t binary_search_index(const int *a, size_t n, int target);

#endif
