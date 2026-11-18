#include "floyd.h"
#include "intlist.h"
#include "tree.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    LinkNode a = {1, NULL}, b = {2, NULL}, c = {3, NULL};
    a.next = &b;
    b.next = &c;
    assert(!has_cycle(&a));
    c.next = &b;
    assert(has_cycle(&a));
    assert(cycle_length(&a) == 2);
    assert(cycle_start(&a) == &b);
    printf("Floyd: cycle length = %zu\n", cycle_length(&a));

    IntList *list = list_create();
    assert(list != NULL);
    assert(list_push_back(list, 20));
    assert(list_push_front(list, 10));
    assert(list_push_back(list, 30));
    list_print(list);
    int value;
    assert(list_pop_front(list, &value) && value == 10);
    list_print(list);
    list_destroy(list);

    Node *root = NULL;
    int keys[] = {8, 4, 12, 2, 6, 10, 14};
    for (size_t i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i)
        assert(bst_insert(&root, keys[i]));
    assert(bst_find(root, 6) != NULL);
    assert(bst_find(root, 99) == NULL);
    printf("preorder: ");
    tree_preorder(root);
    putchar('\n');
    printf("inorder: ");
    tree_inorder(root);
    putchar('\n');
    printf("postorder: ");
    tree_postorder(root);
    putchar('\n');
    tree_destroy(root);
    return 0;
}
