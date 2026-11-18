#ifndef TREE_H
#define TREE_H
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *tree_new(int value);
void tree_destroy(Node *root);
void tree_preorder(const Node *root);
void tree_inorder(const Node *root);
void tree_postorder(const Node *root);
const Node *bst_find(const Node *root, int key);
/* Возвращает false только при ошибке выделения памяти.
   Дубликаты игнорируются. root передаётся по адресу, т.к. корень может измениться. */
bool bst_insert(Node **root, int key);
#endif
