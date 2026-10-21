#include <stdio.h>
#include <stddef.h>

/* В этой функции намеренно оставлена одна логическая ошибка. */
static int binary_search(const int *a, size_t n, int target)
{
    size_t left = 0;
    size_t right = n;  /* полуинтервал [left, right) */

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (a[mid] == target) {
            return (int)mid;
        }
        if (a[mid] < target) {
            left = mid;  /* BUG: граница может не сдвинуться */
        } else {
            right = mid;
        }
    }
    return -1;
}

int main(void)
{
    const int numbers[] = {2, 5, 8, 12, 16, 23, 38};
    const size_t count = sizeof numbers / sizeof numbers[0];
    const int target = 23;

    puts("Ищем число 23 в отсортированном массиве...");
    fflush(stdout);

    int index = binary_search(numbers, count, target);
    printf("Индекс: %d\n", index);
    return 0;
}
