#include "avlset.h"
#include <stdlib.h>

/* Define the private tree node type and the contents of AvlSet here. */
struct AvlSet {
    /* TODO: choose representation and invariants. */
    unsigned char placeholder;
};

AvlSet *avlset_create(void) { return calloc(1, sizeof(AvlSet)); }
void avlset_clear(AvlSet *set) { (void)set; /* TODO */ }
void avlset_destroy(AvlSet *set) { if (!set) return; avlset_clear(set); free(set); }
void avlset_insert(AvlSet *set, int32_t key) { (void)set; (void)key; /* TODO */ }
void avlset_delete(AvlSet *set, int32_t key) { (void)set; (void)key; /* TODO */ }
bool avlset_exists(const AvlSet *set, int32_t key) { (void)set; (void)key; return false; /* TODO */ }
bool avlset_next(const AvlSet *set, int32_t key, int32_t *result) { (void)set; (void)key; (void)result; return false; /* TODO */ }
bool avlset_prev(const AvlSet *set, int32_t key, int32_t *result) { (void)set; (void)key; (void)result; return false; /* TODO */ }
bool avlset_kth(const AvlSet *set, uint32_t k, int32_t *result) { (void)set; (void)k; (void)result; return false; /* TODO */ }
uint32_t avlset_rank(const AvlSet *set, int32_t key) { (void)set; (void)key; return 0; /* TODO */ }
uint32_t avlset_range_count(const AvlSet *set, int32_t left, int32_t right) { (void)set; (void)left; (void)right; return 0; /* TODO */ }
int64_t avlset_range_sum(const AvlSet *set, int32_t left, int32_t right) { (void)set; (void)left; (void)right; return 0; /* TODO */ }
void avlset_delete_range(AvlSet *set, int32_t left, int32_t right) { (void)set; (void)left; (void)right; /* TODO */ }
