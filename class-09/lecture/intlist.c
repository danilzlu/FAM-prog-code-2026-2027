#include "intlist.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

struct IntList {
    Node *head;
    Node *tail;
    size_t size;
};

/* Проверка локальных инвариантов занимает O(1). */
static void check(const IntList *list) {
    assert(list != NULL);
    assert((list->size == 0) == (list->head == NULL));
    assert((list->head == NULL) == (list->tail == NULL));
    assert(list->tail == NULL || list->tail->next == NULL);
}

IntList *list_create(void) {
    /* calloc инициализирует указатели NULL, а размер нулём. */
    return calloc(1, sizeof(IntList));
}

void list_clear(IntList *list) {
    if (list == NULL)
        return;
    check(list);
    Node *cur = list->head;
    while (cur != NULL) {
        Node *next = cur->next; /* Сохраняем ДО free(cur). */
        free(cur);
        cur = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
    check(list);
}

void list_destroy(IntList *list) {
    if (list == NULL)
        return;
    list_clear(list);
    free(list);
}

bool list_push_front(IntList *list, int value) {
    if (list == NULL || list->size == SIZE_MAX)
        return false;
    check(list);
    Node *node = malloc(sizeof(*node));
    if (node == NULL)
        return false; /* При ошибке список не меняется. */
    node->value = value;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
    ++list->size;
    check(list);
    return true;
}

bool list_push_back(IntList *list, int value) {
    if (list == NULL || list->size == SIZE_MAX)
        return false;
    check(list);
    Node *node = malloc(sizeof(*node));
    if (node == NULL)
        return false;
    node->value = value;
    node->next = NULL;
    if (list->tail == NULL)
        list->head = node;
    else
        list->tail->next = node;
    list->tail = node;
    ++list->size;
    check(list);
    return true;
}

bool list_pop_front(IntList *list, int *out) {
    if (list == NULL || out == NULL || list->head == NULL)
        return false;
    check(list);
    Node *old = list->head;
    *out = old->value;
    list->head = old->next;
    free(old);
    --list->size;
    if (list->head == NULL)
        list->tail = NULL; /* Последний узел! */
    check(list);
    return true;
}

bool list_front(const IntList *list, int *out) {
    if (list == NULL || out == NULL || list->head == NULL)
        return false;
    *out = list->head->value;
    return true;
}

size_t list_size(const IntList *list) {
    return list == NULL ? 0 : list->size;
}

bool list_empty(const IntList *list) {
    return list == NULL || list->size == 0;
}

void list_print(const IntList *list) {
    if (list == NULL) {
        puts("(null list)");
        return;
    }
    putchar('[');
    for (const Node *p = list->head; p != NULL; p = p->next) {
        if (p != list->head)
            printf(", ");
        printf("%d", p->value);
    }
    puts("]");
}
