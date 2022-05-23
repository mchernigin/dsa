#include <stdio.h>

#define RBT_IMPLEMENTATION
#include "rbt.h"

int
main(void)
{
    printf("Enter number of elements to insert: ");
    int n;
    scanf("%d", &n);
    printf("Enter elements to insert: ");
    rbt_t *rbt = NULL;
    for (int x, i = 0; i < n; ++i) {
        scanf("%d", &x);
        rbt = rbt_insert(rbt, x);
        rbt_print_preorder(rbt);
        putchar('\n');
    }

    printf("Enter number of elements to remove: ");
    scanf("%d", &n);
    printf("Enter elements to remove: ");
    for (int x, i = 0; i < n; ++i) {
        scanf("%d", &x);
        rbt = rbt_delete(rbt, x);
        rbt_print_preorder(rbt);
        putchar('\n');
    }

    return 0;
}
