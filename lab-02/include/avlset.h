#ifndef AVLSET_H
#define AVLSET_H
#include <stdbool.h>
#include <stdint.h>

typedef struct AvlSet AvlSet;

AvlSet *avlset_create(void);
void avlset_clear(AvlSet *set);
void avlset_destroy(AvlSet *set);

void avlset_insert(AvlSet *set, int32_t key);
void avlset_delete(AvlSet *set, int32_t key);

bool avlset_exists(const AvlSet *set, int32_t key);

bool avlset_next(const AvlSet *set, int32_t key, int32_t *result);
bool avlset_prev(const AvlSet *set, int32_t key, int32_t *result);

bool avlset_kth(const AvlSet *set, uint32_t k, int32_t *result);

uint32_t avlset_rank(const AvlSet *set, int32_t key);

uint32_t avlset_range_count(const AvlSet *set, int32_t left, int32_t right);
int64_t avlset_range_sum(const AvlSet *set, int32_t left, int32_t right);

void avlset_delete_range(AvlSet *set, int32_t left, int32_t right);
#endif
