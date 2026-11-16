#include "sorting.h"

int *min_element(int *a, size_t n) {
    if (n == 0)
        return NULL;

    int *best = a;
    for (size_t i = 1; i < n; ++i) {
        if (a[i] < *best)
            best = &a[i];
    }
    return best;
}

void swap_int(int *x, int *y) {
    if (x == y)
        return;
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selection_sort(int *a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        /* Ищем минимум только в ещё не отсортированном суффиксе. */
        int *minimum = min_element(a + i, n - i);
        swap_int(&a[i], minimum);
    }
}

void insert_sorted_prefix(int *a, size_t sorted_count, int value) {
    size_t j = sorted_count;
    /* Сдвигаем вправо элементы, которые больше вставляемого. */
    while (j > 0 && a[j - 1] > value) {
        a[j] = a[j - 1];
        --j;
    }
    a[j] = value;
}

void insertion_sort(int *a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        /* a[0..i) уже отсортирован; a[i] сохраняем до сдвигов. */
        int value = a[i];
        insert_sorted_prefix(a, i, value);
    }
}
