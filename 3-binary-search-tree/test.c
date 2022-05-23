#include <stdio.h>

#include "bst.h"

int
main(void)
{
    int arr[] = {10, 5, 34, 88, 1, 3, 15, 67, 91, 4, 23, 102};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    bst_t * bst = NULL;
    for (int i = 0; i < arr_size; ++i)
        bst = bst_insert(bst, arr[i]);

    printf("Preorder:  ");
    bst_print_preorder(bst);
    printf("\nInorder:   ");
    bst_print_inorder(bst);
    printf("\nPostorder: ");
    bst_print_postorder(bst);
    printf("\n");

    bst_t * bst_find_res = bst_find(bst, 34);
    printf("`bst_find(bst, 34)` resulted in bst node such as:\n");
    printf("\tvalue: %d\n", bst_find_res->value);
    printf("\tinorder: ");
    bst_print_inorder(bst_find_res);
    printf("\n");

    bst = bst_remove(bst, 34);
    printf("Preorder after deleting 34: ");
    bst_print_preorder(bst);
    printf("\n");

    return 0;
}
