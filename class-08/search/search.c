#include "search.h"

ptrdiff_t linear_search_index(const int *a, size_t n, int target) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] == target)
            return (ptrdiff_t)i;
    }
    return -1;
}

const int *linear_search_ptr(const int *a, size_t n, int target) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] == target)
            return &a[i];
    }
    return NULL;
}

const void *linear_search_generic(const void *base, size_t n, size_t element_size, const void *key,
                                  int (*compare)(const void *, const void *)) {
    /* void* не поддерживает арифметику указателей в стандартном C.
       Переводим адрес в указатель на байты. */
    const unsigned char *bytes = base;
    for (size_t i = 0; i < n; ++i) {
        const void *element = bytes + i * element_size;
        if (compare(element, key) == 0)
            return element;
    }
    return NULL;
}

ptrdiff_t binary_search_index(const int *a, size_t n, int target) {
    /* Инвариант: если target существует, он находится в [left, right). */
    size_t left = 0;
    size_t right = n;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (a[mid] == target)
            return (ptrdiff_t)mid;
        if (a[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return -1;
}
