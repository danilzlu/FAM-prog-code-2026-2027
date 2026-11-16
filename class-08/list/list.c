#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_print(const Node *head) {
    printf("[");
    for (const Node *p = head; p != NULL; p = p->next) {
        if (p != head)
            printf(", ");
        printf("%d", p->value);
    }
    printf("]\n");
}

Node *list_insert_after(Node *position, int value) {
    if (position == NULL)
        return NULL;

    Node *node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;

    node->value = value;
    /* Порядок важен: сначала сохраняем старую ссылку. */
    node->next = position->next;
    position->next = node;
    return node;
}

void list_free(Node *head) {
    // ваш код здесь
}
