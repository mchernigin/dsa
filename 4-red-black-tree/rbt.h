#ifndef RBT_H
#define RBT_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum node_color_t {
    NC_BLACK,
    NC_RED,
} node_color_t;

typedef struct rbt_t {
    int value;
    node_color_t color;
    struct rbt_t *left;
    struct rbt_t *right;
    struct rbt_t *parent;
} rbt_t;

rbt_t *rbt_create_null(rbt_t *parent);
rbt_t *rbt_create(int value);

void rbt_print_preorder(rbt_t *rbt);
void rbt_print_inorder(rbt_t *rbt);
void rbt_print_postorder(rbt_t *rbt);

rbt_t *rbt_find(rbt_t *rbt, int value);
rbt_t *rbt_min(rbt_t *rbt);
rbt_t *rbt_max(rbt_t *rbt);

rbt_t *rbt_rotate_left(rbt_t *rbt, rbt_t *node);
rbt_t *rbt_rotate_right(rbt_t *rbt, rbt_t *node);

rbt_t *rbt_transplant(rbt_t *rbt, rbt_t *target, rbt_t *other);

rbt_t *rbt_insert(rbt_t *rbt, int value);
rbt_t *rbt_fix_insert(rbt_t *rbt, rbt_t *node);

rbt_t *rbt_fix_delete(rbt_t *rbt, rbt_t *node);
rbt_t *rbt_delete(rbt_t *rbt, int value);

#ifdef __cplusplus
}
#endif

#endif // RBT_H

#ifdef RBT_IMPLEMENTATION

rbt_t *
rbt_create_null(rbt_t *parent)
{
    rbt_t *rbt = (rbt_t *) malloc(sizeof(rbt_t));
    rbt->value = 0;
    rbt->color = NC_BLACK;
    rbt->left = NULL;
    rbt->right = NULL;
    rbt->parent = parent;

    return (rbt);
}

rbt_t *
rbt_create(int value)
{
    rbt_t *rbt = (rbt_t *) malloc(sizeof(rbt_t));
    rbt->value = value;
    rbt->color = NC_RED;
    rbt->left = rbt_create_null(rbt);
    rbt->right = rbt_create_null(rbt);
    rbt->parent = NULL;

    return (rbt);
}

bool
rbt_is_null(rbt_t *node)
{
    return (!node || (!node->left && !node->right));
}

rbt_t *
rbt_find(rbt_t *rbt, int value)
{
    if (rbt_is_null(rbt) || rbt->value == value)
        return (rbt);
    if (value < rbt->value)
        return (rbt_find(rbt->left, value));
    return (rbt_find(rbt->right, value));
}

void
rbt_print_preorder(rbt_t *rbt)
{
    if (rbt_is_null(rbt)) return;

    printf("%d%c ", rbt->value, (rbt->color == NC_RED ? 'R' : 'B'));
    rbt_print_preorder(rbt->left);
    rbt_print_preorder(rbt->right);
}

void
rbt_print_inorder(rbt_t *rbt)
{
    if (rbt_is_null(rbt)) return;

    rbt_print_inorder(rbt->left);
    printf("%d ", rbt->value);
    rbt_print_inorder(rbt->right);
}

void
rbt_print_postorder(rbt_t *rbt)
{
    if (rbt_is_null(rbt)) return;

    rbt_print_postorder(rbt->left);
    rbt_print_postorder(rbt->right);
    printf("%d ", rbt->value);
}

rbt_t *
rbt_rotate_left(rbt_t *rbt, rbt_t *node)
{
    assert(!rbt_is_null(node) && !rbt_is_null(node->right));
    rbt_t *sibling = node->right;

    node->right = sibling->left;
    if (!rbt_is_null(sibling->left))
        sibling->left->parent = node;

    sibling->parent = node->parent;
    if (!node->parent)
        rbt = sibling;
    else if (node == node->parent->left)
        node->parent->left = sibling;
    else
        node->parent->right = sibling;

    sibling->left = node;
    node->parent = sibling;

    return (rbt);
}

rbt_t *
rbt_rotate_right(rbt_t *rbt, rbt_t *node)
{
    assert(!rbt_is_null(node) && !rbt_is_null(node->left));
    rbt_t *sibling = node->left;

    node->left = sibling->right;
    if (!rbt_is_null(sibling->right))
        sibling->right->parent = node;

    sibling->parent = node->parent;
    if (!node->parent)
        rbt = sibling;
    else if (node == node->parent->left)
        node->parent->left = sibling;
    else
        node->parent->right = sibling;

    sibling->right = node;
    node->parent = sibling;

    return (rbt);
}

rbt_t *
rbt_transplant(rbt_t *rbt, rbt_t *target, rbt_t *other)
{
    assert(!rbt_is_null(target) && !rbt_is_null(rbt));

    if (!target->parent)
        rbt = other;
    else if (target == target->parent->left)
        target->parent->left = other;
    else
        target->parent->right = other;

    if (other)
        other->parent = target->parent;

    return (rbt);
}

rbt_t *
rbt_min(rbt_t *rbt)
{
    assert(!rbt_is_null(rbt));

    // Left child is always less when its parent,
    // which means that to find the minimum
    // we should always go to the left child.
    while (!rbt_is_null(rbt->left))
        rbt = rbt->left;
    return (rbt);
}

rbt_t *
rbt_max(rbt_t *rbt)
{
    assert(!rbt_is_null(rbt));

    // Right child is always greater when its parent,
    // which means that to find the maximum
    // we should always go to the right child.
    while (!rbt_is_null(rbt->right))
        rbt = rbt->right;
    return (rbt);
}

rbt_t *
rbt_fix_insert(rbt_t *rbt, rbt_t *node)
{
    assert(!rbt_is_null(node));

    if (!node->parent)
        // Case #1 (root)
        node->color = NC_BLACK;
    else if (!node->parent->parent)
        return (rbt);

    rbt_t *uncle;
    while (node->parent && node->parent->color == NC_RED) {
        if (node->parent == node->parent->parent->right) {
            uncle = node->parent->parent->left;
            if (!rbt_is_null(uncle) && uncle->color == NC_RED) {
                // Case #2 (Red uncle)
                uncle->color = NC_BLACK;
                node->parent->color = NC_BLACK;
                node->parent->parent->color = NC_RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Case #3 (Black uncle + triangle)
                    node = node->parent;
                    rbt = rbt_rotate_right(rbt, node);
                }
                // Case #4 (Black uncle + line)
                node->parent->color = NC_BLACK;
                node->parent->parent->color = NC_RED;
                rbt = rbt_rotate_left(rbt, node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->right;
            if (!rbt_is_null(uncle) && uncle->color == NC_RED) {
                // Case #2 (Red uncle)
                uncle->color = NC_BLACK;
                node->parent->color = NC_BLACK;
                node->parent->parent->color = NC_RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Case #3 (Black uncle + triangle)
                    node = node->parent;
                    rbt = rbt_rotate_left(rbt, node);
                }
                // Case #4 (Black uncle + line)
                node->parent->color = NC_BLACK;
                node->parent->parent->color = NC_RED;
                rbt = rbt_rotate_right(rbt, node->parent->parent);
            }
        }
    }
    rbt->color = NC_BLACK;
    return (rbt);
}

rbt_t *
rbt_insert(rbt_t *rbt, int value)
{
    // Find where new element will be inserted
    rbt_t *parent = NULL;
    for (rbt_t *it = rbt; it && !rbt_is_null(it);) {
        parent = it;
        it = (value < it->value ? it->left : it->right);
    }

    // Create a new node from given value
    rbt_t *new_node = rbt_create(value);
    new_node->parent = parent;
    if (!parent)
        rbt = new_node;
    else if (value < parent->value)
        parent->left = new_node;
    else
        parent->right = new_node;

    rbt = rbt_fix_insert(rbt, new_node);

    return (rbt);
}

rbt_t *
rbt_fix_delete(rbt_t *rbt, rbt_t *node)
{
    rbt_t *sibling;
    while (node->parent && node->color == NC_BLACK) {
        if (node == node->parent->left) {
            sibling = node->parent->right;
            if (sibling->color == NC_RED) {
                sibling->color = NC_BLACK;
                node->parent->color = NC_RED;
                rbt = rbt_rotate_left(rbt, node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == NC_BLACK &&
                sibling->right->color == NC_BLACK) {
                sibling->color = NC_RED;
                node = node->parent;
            } else {
                if (sibling->right->color == NC_BLACK) {
                    sibling->left->color = NC_BLACK;
                    sibling->color = NC_RED;
                    rbt = rbt_rotate_right(rbt, sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = NC_BLACK;
                sibling->right->color = NC_BLACK;
                rbt = rbt_rotate_left(rbt, node->parent);
                node = rbt;
            }
        } else {
            sibling = node->parent->left;
            if (sibling->color == NC_RED) {
                sibling->color = NC_BLACK;
                node->parent->color = NC_RED;
                rbt = rbt_rotate_right(rbt, node->parent);
                sibling = node->parent->left;
            }

            if (sibling->left->color == NC_BLACK &&
                sibling->right->color == NC_BLACK) {
                sibling->color = NC_RED;
                node = node->parent;
            } else {
                if (sibling->left->color == NC_BLACK) {
                    sibling->right->color = NC_BLACK;
                    sibling->color = NC_RED;
                    rbt = rbt_rotate_left(rbt, sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = NC_BLACK;
                sibling->left->color = NC_BLACK;
                rbt = rbt_rotate_right(rbt, node->parent);
                node = rbt;
            }

        }
    }
    node->color = NC_BLACK;

    return (rbt);
}

rbt_t *
rbt_delete(rbt_t *rbt, int value)
{
    rbt_t *tbd = rbt_find(rbt, value);
    if (rbt_is_null(tbd)) return (rbt);

    node_color_t orig_color = tbd->color;
    rbt_t *x;
    if (rbt_is_null(tbd->left) || rbt_is_null(tbd->right)) {
        x = (rbt_is_null(tbd->left) ? tbd->right : tbd->left);
        rbt = rbt_transplant(rbt, tbd, x);
    } else {
        rbt_t *y = rbt_min(tbd->right);
        orig_color = y->color;
        x = y->right;
        if (y->parent == tbd) {
            x->parent = y;
        } else {
            rbt = rbt_transplant(rbt, y, y->right);
            y->right = tbd->right;
            y->right->parent = y;
        }
        rbt = rbt_transplant(rbt, tbd, y);
        y->left = tbd->left;
        y->left->parent = y;
        y->color = tbd->color;
    }
    free(tbd);

    if (orig_color == NC_BLACK)
        rbt = rbt_fix_delete(rbt, x);

    return (rbt);
}

#endif // RBT_IMPLEMENTATION
