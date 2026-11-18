#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

Node *tree_new(int value) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    *node = (Node){.value = value, .left = NULL, .right = NULL};
    return node;
}

void tree_preorder(const Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->value); /* N */
    tree_preorder(root->left);  /* L */
    tree_preorder(root->right); /* R */
}

void tree_inorder(const Node *root) {
    if (root == NULL)
        return;
    tree_inorder(root->left);   /* L */
    printf("%d ", root->value); /* N */
    tree_inorder(root->right);  /* R */
}

void tree_postorder(const Node *root) {
    if (root == NULL)
        return;
    tree_postorder(root->left);  /* L */
    tree_postorder(root->right); /* R */
    printf("%d ", root->value);  /* N */
}

void tree_destroy(Node *root) {
    if (root == NULL)
        return;
    tree_destroy(root->left); /* Сначала дети, затем родитель. */
    tree_destroy(root->right);
    free(root);
}

const Node *bst_find(const Node *root, int key) {
    while (root != NULL) {
        if (key == root->value)
            return root;
        root = key < root->value ? root->left : root->right;
    }
    return NULL;
}

bool bst_insert(Node **root, int key) {
    if (root == NULL)
        return false;
    if (*root == NULL) {
        *root = tree_new(key);
        return *root != NULL;
    }
    if (key == (*root)->value)
        return true;
    if (key < (*root)->value)
        return bst_insert(&(*root)->left, key);
    return bst_insert(&(*root)->right, key);
}
