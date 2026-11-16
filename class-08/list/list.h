#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

/* Печатает значения узлов в одну строку. Список должен быть без цикла. */
void list_print(const Node *head);

/* Создаёт новый узел со значением value и вставляет после position.
   Возвращает указатель на новый узел или NULL при ошибке выделения памяти.
   position должен указывать на существующий узел. */
Node *list_insert_after(Node *position, int value);

/* Освобождает все узлы ациклического списка. */
void list_free(Node *head);

#endif
