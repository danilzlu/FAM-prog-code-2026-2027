#include "../lecture/floyd.h"
#include "../lecture/intlist.h"
#include "../lecture/tree.h"
#include "../seminar/exercises.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

static void test_list(void) {
    IntList *l = list_create(); assert(l);
    int x = -1;
    assert(list_empty(l) && list_size(l) == 0);
    assert(!list_pop_front(l, &x));
    assert(list_push_back(l, 2) && list_push_front(l, 1));
    assert(list_push_back(l, 3) && list_size(l) == 3);
    assert(list_front(l, &x) && x == 1);
    assert(list_pop_front(l, &x) && x == 1);
    assert(list_pop_front(l, &x) && x == 2);
    assert(list_pop_front(l, &x) && x == 3);
    assert(list_empty(l));
    assert(list_push_back(l, 4));
    list_clear(l);
    assert(list_empty(l));
    list_destroy(l);
    list_destroy(NULL);
}
static void test_floyd(void) {
    LinkNode a = {1,NULL}, b = {2,NULL}, c = {3,NULL}, d = {4,NULL};
    assert(!has_cycle(NULL) && cycle_length(NULL) == 0);
    a.next=&b; b.next=&c; c.next=&d;
    assert(!has_cycle(&a) && cycle_start(&a) == NULL);
    d.next=&b;
    assert(has_cycle(&a) && cycle_length(&a)==3 && cycle_start(&a)==&b);
    d.next=NULL; a.next=&a;
    assert(has_cycle(&a) && cycle_length(&a)==1 && cycle_start(&a)==&a);
}
static void test_tree(void) {
    Node *r=NULL;
    assert(tree_size(r)==0 && tree_height(r)==0 && is_bst(r));
    int keys[]={8,4,12,2,6,10,14};
    for(size_t i=0;i<7;i++) assert(bst_insert(&r,keys[i]));
    assert(bst_insert(&r,8) && tree_size(r)==7);
    assert(tree_size(r)==7 && tree_height(r)==3 && tree_count_leaves(r)==4);
    assert(tree_sum_at_depth(r,0)==8);
    assert(tree_sum_at_depth(r,1)==16);
    assert(tree_sum_at_depth(r,2)==32);
    assert(tree_sum_at_depth(r,10)==0);
    assert(is_bst(r));
    assert(bst_lca(r,2,6)->value==4);
    assert(bst_lca(r,2,14)->value==8);
    assert(bst_lca(r,4,6)->value==4);
    assert(bst_find(r,10) && !bst_find(r,11));
    Node *copy=NULL;
    for(size_t i=0;i<7;i++) assert(bst_insert(&copy,keys[i]));
    assert(tree_equal(r,copy));
    tree_mirror(copy);
    assert(!is_bst(copy) && !tree_equal(r,copy));
    tree_mirror(copy);
    assert(tree_equal(r,copy));
    tree_destroy(copy);
    /* Локальные сравнения выполняются, но ключ нарушает ограничение предка. */
    r->left->right->value=9;
    assert(!is_bst(r));
    r->left->right->value=6;
    tree_destroy(r);
    Node *edge=NULL;
    assert(bst_insert(&edge,INT_MIN));
    assert(bst_insert(&edge,INT_MAX));
    assert(is_bst(edge));
    tree_destroy(edge);
}
int main(void) {
    test_list(); test_floyd(); test_tree();
    puts("All tests passed.");
    return 0;
}
