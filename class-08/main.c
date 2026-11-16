#include "list/list.h"
#include "search/search.h"
#include "sorting/sorting.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int(const void *lhs, const void *rhs) {
    int a = *(const int *)lhs;
    int b = *(const int *)rhs;
    /* В отличие от a - b, эта запись не вызывает переполнение int. */
    return (a > b) - (a < b);
}

static void print_array(const int *a, size_t n) {
    for (size_t i = 0; i < n; ++i)
        printf("%d%s", a[i], i + 1 == n ? "\n" : " ");
}

int main(void) {
    int a[] = {7, 2, 9, 2, 5};
    size_t n = sizeof(a) / sizeof(a[0]);
    int key = 9;

    assert(linear_search_index(a, n, key) == 2);
    assert(linear_search_index(a, n, 100) == -1);
    assert(linear_search_ptr(a, n, key) == &a[2]);
    assert(linear_search_generic(a, n, sizeof(a[0]), &key, compare_int) == &a[2]);

    selection_sort(a, n);
    printf("Selection sort: ");
    print_array(a, n);
    assert(binary_search_index(a, n, 9) == 4);

    int b[] = {6, 1, 4, 2, 3};
    insertion_sort(b, sizeof(b) / sizeof(b[0]));
    printf("Insertion sort: ");
    print_array(b, sizeof(b) / sizeof(b[0]));

    int c[6] = {1, 3, 5};
    insert_sorted_prefix(c, 3, 4);
    printf("Insert 4: ");
    print_array(c, 4);

    /* Первый узел создан отдельно; вставка выполняется после него. */
    Node *head = malloc(sizeof(*head));
    if (head == NULL) {
        perror("malloc");
        return 1;
    }
    head->value = 10;
    head->next = NULL;

    if (list_insert_after(head, 30) == NULL || list_insert_after(head, 20) == NULL) {
        perror("list_insert_after");
        list_free(head);
        return 1;
    }
    printf("Linked list: ");
    list_print(head);
    list_free(head);
    return 0;
}
