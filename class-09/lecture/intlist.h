#ifndef INTLIST_H
#define INTLIST_H
#include <stdbool.h>
#include <stddef.h>
typedef struct IntList IntList;
IntList *list_create(void);
void list_destroy(IntList *list);
void list_clear(IntList *list);
bool list_push_front(IntList *list, int value);
bool list_push_back(IntList *list, int value);
bool list_pop_front(IntList *list, int *out);
bool list_front(const IntList *list, int *out);
size_t list_size(const IntList *list);
bool list_empty(const IntList *list);
void list_print(const IntList *list);
#endif
