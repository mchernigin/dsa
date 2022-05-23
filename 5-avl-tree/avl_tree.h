#ifndef MXA_AVL_TREE_H
#define MXA_AVL_TREE_H

#include <cassert>

namespace mxa {
    template<typename T>
    struct AVL_Node {
        T value;
        int height;
        AVL_Node<T> *left;
        AVL_Node<T> *right;
        AVL_Node<T> *parent;

        // Constructor:
        explicit AVL_Node(const T& val);
    };

    template<typename T>
    class AVL_Tree {
    public:
        // Constructor:
        AVL_Tree();

        // Destructor:
        ~AVL_Tree();

        // Methods:
        void print_preorder() const;
        void print_inorder() const;
        void print_postorder() const;

        AVL_Node<T> *find(const T& value) const;
        void insert(const T& value);
        void remove(const T& value);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const AVL_Tree<U>& tree);

    private:
        AVL_Node<T> *root;

        AVL_Node<T> *right_rotate(AVL_Node<T> *node);
        AVL_Node<T> *left_rotate(AVL_Node<T> *node);
        AVL_Node<T> *find_helper(AVL_Node<T> *node, const T& value) const;
        AVL_Node<T> *successor(AVL_Node<T> *node) const;
        AVL_Node<T> *insert_helper(AVL_Node<T> *node, const T& value);
        AVL_Node<T> *remove_helper(AVL_Node<T> *node, const T& value);
    };

    // Helpers:
    template<typename T>
    void print_preorder_helper(std::ostream& out, const AVL_Node<T> *node);

    template<typename T>
    void print_inorder_helper(std::ostream& out, const AVL_Node<T> *node);

    template<typename T>
    void print_postorder_helper(std::ostream& out, const AVL_Node<T> *node);

    template<typename T>
    int get_height(const AVL_Node<T> *node);

    template<typename T>
    int get_balance_factor(const AVL_Node<T> *node);

    // Node constructor:
    template<typename T>
    AVL_Node<T>::AVL_Node(const T& val) : value(val), height(1), left(nullptr),
        right(nullptr), parent(nullptr) {}

    // Constructor:
    template<typename T>
    AVL_Tree<T>::AVL_Tree() : root(nullptr) {}

    // Destructor:
    template<typename T>
    AVL_Tree<T>::~AVL_Tree()
    {
        while (this->root != nullptr) {
            remove(this->root->value);
        }
    }

    // Methods:
    template<typename T>
    void AVL_Tree<T>::print_preorder() const
    {
        print_preorder_helper(std::cout, this->root);
        std::cout << "\033[1D";
    }

    template<typename T>
    void AVL_Tree<T>::print_inorder() const
    {
        print_inorder_helper(std::cout, this->root);
        std::cout << "\033[1D";
    }

    template<typename T>
    void AVL_Tree<T>::print_postorder() const
    {
        print_postorder_helper(std::cout, this->root);
        std::cout << "\033[1D";
    }

    template<typename T>
    AVL_Node<T> *AVL_Tree<T>::find(const T& value) const
    {
        return find_helper(this->root, value);
    }

    template<typename T>
    AVL_Node<T> *AVL_Tree<T>::find_helper(AVL_Node<T> *node, const T& value) const
    {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return find_helper(node->left, value);
        } else {
            return find_helper(node->right, value);
        }
    }

    template<typename T>
    AVL_Node<T> *AVL_Tree<T>::successor(AVL_Node<T> *node) const
    {
        assert(node && node->right);

        auto it = node->right;
        while (it->left != nullptr) {
            it = it->left;
        }

        return it;
    }

    template<typename T>
    void AVL_Tree<T>::insert(const T& value)
    {
        this->root = insert_helper(this->root, value);
    }

    template<typename T>
    AVL_Node<T> *AVL_Tree<T>::insert_helper(AVL_Node<T> *node, const T& value)
    {
        // Insert new node
        if (node == nullptr) {
            return (new AVL_Node<T>(value));
        }
        if (value < node->value) {
            node->left = insert_helper(node->left, value);
        } else if (value > node->value) {
            node->right = insert_helper(node->right, value);
        } else {
            return node;
        }

        // Update heights and balance
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        int balance_factor = get_balance_factor(node);
        if (balance_factor > 1) {
            if (value < node->left->value) {
                return right_rotate(node);
            } else if (value > node->left->value) {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
        }
        if (balance_factor < -1) {
            if (value > node->right->value) {
                return left_rotate(node);
            } else if (value < node->right->value) {
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }
        }
        return node;
    }

    template<typename T>
    void AVL_Tree<T>::remove(const T& value)
    {
        this->root = remove_helper(this->root, value);
    }

    template<typename T>
    AVL_Node<T> *AVL_Tree<T>::remove_helper(AVL_Node<T> *node, const T& value)
    {
        // Remove element
        if (node == nullptr) {
            return node;
        }
        if (value < node->value) {
            node->left = remove_helper(node->left, value);
        } else if (value > node->value) {
            node->right = remove_helper(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                auto tmp = (node->left == nullptr ? node->right : node->left);
                if (tmp == nullptr) {
                    tmp = node;
                    node = nullptr;
                } else {
                    *node = *tmp;
                }
                delete tmp;
            } else {
                node->value = successor(node)->value;
                node->right = remove_helper(node->right, node->value);
            }
        }

        if (node == nullptr) {
            return node;
        }

        // Update heights and balance
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        int balance_factor = get_balance_factor(node);
        if (balance_factor > 1) {
            if (get_balance_factor(node->left) >= 0) {
                return right_rotate(node);
            } else {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
        }
        if (balance_factor < -1) {
            if (get_balance_factor(node->right) <= 0) {
                return left_rotate(node);
            } else {
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }
        }
        return node;
    }

    template <typename T>
    AVL_Node<T> *AVL_Tree<T>::right_rotate(AVL_Node<T> *node)
    {
        auto parent = node->left;
        auto left = parent->right;
        parent->right = node;
        node->left = left;
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        parent->height = 1 + std::max(get_height(parent->left),
                                      get_height(parent->right));
        return parent;
    }

    template <typename T>
    AVL_Node<T> *AVL_Tree<T>::left_rotate(AVL_Node<T> *node)
    {
        auto parent = node->right;
        auto right = parent->left;
        parent->left = node;
        node->right = right;
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        parent->height = 1 + std::max(get_height(parent->left),
                                      get_height(parent->right));
        return parent;
    }

    // Helpers:
    template<typename T>
    void print_preorder_helper(std::ostream& out, const AVL_Node<T> *node)
    {
        if (node == nullptr) {
            return;
        }

        out << node->value << ' ';
        print_preorder_helper(out, node->left);
        print_preorder_helper(out, node->right);
    }

    template<typename T>
    void print_inorder_helper(std::ostream& out, const AVL_Node<T> *node)
    {
        if (node == nullptr) {
            return;
        }

        print_inorder_helper(out, node->left);
        out << node->value << ' ';
        print_inorder_helper(out, node->right);
    }

    template<typename T>
    void print_postorder_helper(std::ostream& out, const AVL_Node<T> *node)
    {
        if (node == nullptr) {
            return;
        }

        print_postorder_helper(out, node->left);
        print_postorder_helper(out, node->right);
        out << node->value << ' ';
    }

    template<typename T>
    int get_height(const AVL_Node<T> *node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    template<typename T>
    int get_balance_factor(const AVL_Node<T> *node)
    {
        if (node == nullptr) {
            return 0;
        }
        return get_height(node->left) - get_height(node->right);
    }

    template<typename U>
    std::ostream& operator<<(std::ostream& out, const AVL_Tree<U>& tree)
    {
        print_preorder_helper(out, tree.root);
        out << "\033[1D";

        return out;
    }

}

#endif // MXA_AVL_TREE_H
