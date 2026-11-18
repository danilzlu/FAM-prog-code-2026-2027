#ifndef FLOYD_H
#define FLOYD_H
#include <stdbool.h>
#include <stddef.h>

typedef struct LinkNode {
    int value;
    struct LinkNode *next;
} LinkNode;

bool has_cycle(const LinkNode *head);
size_t cycle_length(const LinkNode *head);
const LinkNode *cycle_start(const LinkNode *head);
#endif
