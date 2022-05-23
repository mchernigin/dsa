#include <iostream>

#include "avl_tree.h"

int main(void)
{
    std::cout << "Enter number of element to insert: ";
    int n;
    std::cin >> n;
    std::cout << "Enter elements to insert: ";
    mxa::AVL_Tree<int> tree;
    for (int x, i = 0; i < n; ++i) {
        std::cin >> x;
        tree.insert(x);
        std::cout << "AVL Tree Preorder: " << tree << '\n';
    }

    std::cout << "Enter number of elements to remove: ";
    std::cin >> n;
    std::cout << "Enter elements to remove: ";
    for (int x, i = 0; i < n; ++i) {
        std::cin >> x;
        tree.remove(x);
    }
    std::cout << "AVL Tree Preorder: " << tree << '\n';

    return 0;
}
