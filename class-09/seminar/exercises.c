#include "exercises.h"

size_t tree_size(const Node *root) {
    if (root == NULL)
        return 0;
    return 1 + tree_size(root->left) + tree_size(root->right);
}

size_t tree_height(const Node *root) {
    if (root == NULL)
        return 0;
    size_t left = tree_height(root->left);
    size_t right = tree_height(root->right);
    return 1 + (left > right ? left : right);
}

/* Проверка BST через строго возрастающий inorder.
   Сравниваем со значением предыдущего узла, не только с детьми. */
static bool inorder_increasing(const Node *root, const Node **prev) {
    if (root == NULL)
        return true;
    if (!inorder_increasing(root->left, prev))
        return false;
    if (*prev != NULL && (*prev)->value >= root->value)
        return false;
    *prev = root;
    return inorder_increasing(root->right, prev);
}

bool is_bst(const Node *root) {
    const Node *prev = NULL;
    return inorder_increasing(root, &prev);
}

const Node *bst_lca(const Node *root, int a, int b) {
    while (root != NULL) {
        if (a < root->value && b < root->value)
            root = root->left;
        else if (a > root->value && b > root->value)
            root = root->right;
        else
            return root; /* Ключи разошлись по сторонам или один равен root. */
    }
    return NULL;
}

void tree_mirror(Node *root) {
    if (root == NULL)
        return;
    Node *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    tree_mirror(root->left);
    tree_mirror(root->right);
}

size_t tree_count_leaves(const Node *root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return tree_count_leaves(root->left) + tree_count_leaves(root->right);
}

long long tree_sum_at_depth(const Node *root, size_t depth) {
    if (root == NULL)
        return 0;
    if (depth == 0)
        return root->value;
    return tree_sum_at_depth(root->left, depth - 1) + tree_sum_at_depth(root->right, depth - 1);
}

bool tree_equal(const Node *a, const Node *b) {
    if (a == NULL || b == NULL)
        return a == b;
    return a->value == b->value && tree_equal(a->left, b->left) && tree_equal(a->right, b->right);
}
