#ifndef EXERCISES_H
#define EXERCISES_H
#include "../lecture/tree.h"
#include <stdbool.h>
#include <stddef.h>

size_t tree_size(const Node *root);
size_t tree_height(const Node *root); /* Число узлов в самом длинном пути. */
bool is_bst(const Node *root);        /* Ключи строго различны. */
/* Предполагается, что a и b есть в BST. Иначе результат не определён контрактом. */
const Node *bst_lca(const Node *root, int a, int b);
void tree_mirror(Node *root);
/* Резервные задачи. */
size_t tree_count_leaves(const Node *root);
long long tree_sum_at_depth(const Node *root, size_t depth);
bool tree_equal(const Node *a, const Node *b);
#endif
