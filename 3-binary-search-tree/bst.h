#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bst_t {
    int value;
    struct bst_t * left;
    struct bst_t * right;
} bst_t;

bst_t *
bst_create(int value)
{
    bst_t * bst = (bst_t *) malloc(sizeof(bst_t));
    bst->value  = value;
    bst->left   = NULL;
    bst->right  = NULL;

    return (bst);
}

bst_t *
bst_insert(bst_t * bst, int value)
{
    if (!bst) {
        return (bst_create(value));
    }

    if (value < bst->value) {
        bst->left = bst_insert(bst->left, value);
    } else {
        bst->right = bst_insert(bst->right, value);
    }

    return (bst);
}

bst_t *
bst_find(bst_t * bst, int value)
{
    if (!bst || value == bst->value) {
        return (bst);
    }

    if (value < bst->value) {
        return (bst_find(bst->left, value));
    }
    if (value > bst->value) {
        return (bst_find(bst->right, value));
    }

     __builtin_unreachable();
}

bst_t *
bst_min(bst_t * bst)
{
    bst_t * tmp = bst;
    while (tmp && tmp->left) {
        tmp = tmp->left;
    }

    return tmp;
}

bst_t *
bst_max(bst_t * bst)
{
    bst_t * tmp = bst;
    while (tmp && tmp->right) {
        tmp = tmp->right;
    }

    return tmp;
}

bst_t *
bst_remove(bst_t * bst, int value)
{
    if (!bst) {
       return (bst); 
    }

    if (value < bst->value) {
        bst->left = bst_remove(bst->left, value);
    } else if (value > bst->value) {
        bst->right = bst_remove(bst->right, value);
    } else {
        if (!bst->left) {
            bst_t * tmp = bst->right;
            free(bst);
            return (tmp);
        }

        if (!bst->right) {
            bst_t * tmp = bst->left;
            free(bst);
            return (tmp);
        }

        int upper_bound = bst_min(bst->right)->value;
        bst->value = upper_bound;
        bst->right = bst_remove(bst->right, upper_bound);
    }

    return (bst);
}

void
bst_print_preorder(bst_t * bst)
{
    if (!bst) {
        return;
    }

    printf("%d ", bst->value);
    bst_print_preorder(bst->left);
    bst_print_preorder(bst->right);
}

void
bst_print_inorder(bst_t * bst)
{
    if (!bst) {
        return;
    }

    bst_print_inorder(bst->left);
    printf("%d ", bst->value);
    bst_print_inorder(bst->right);
}

void
bst_print_postorder(bst_t * bst)
{
    if (!bst) {
        return;
    }

    bst_print_postorder(bst->left);
    bst_print_postorder(bst->right);
    printf("%d ", bst->value);
}

#endif // BST_H
