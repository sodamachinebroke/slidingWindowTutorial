#include "header/BinaryTree.h"

template<typename T>
Node<T>::Node(T value) : data(value), left(nullptr), right(nullptr) {}

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<typename T>
void BinaryTree<T>::insertNode(T value) {
    auto *newNode = new Node<T>(value);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    std::queue<Node<T> *> q;
    q.push(root);

    while (!q.empty()) {
        Node<T> *current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = newNode;
            return;
        } else {
            q.push(current->right);
        }
    }
}

template<typename T>
void BinaryTree<T>::deleteNode(T value) {
    root = deleteRecursive(root, value);
}

template<typename T>
bool BinaryTree<T>::search(T value) {
    return searchRecursive(root, value);
}

template<typename T>
void BinaryTree<T>::inorder() {
    inorderRecursive(root);
    std::cout << std::endl;
}

template<typename T>
void BinaryTree<T>::preorder() {
    preorderRecursive(root);
    std::cout << std::endl;
}

template<typename T>
void BinaryTree<T>::postorder() {
    postorderRecursive(root);
    std::cout << std::endl;
}

template<typename T>
void BinaryTree<T>::levelOrder() {
    if (root == nullptr) return;

    std::queue<Node<T> *> q;
    q.push(root);

    while (!q.empty()) {
        Node<T> *current = q.front();
        q.pop();

        std::cout << current->data << " ";

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    std::cout << std::endl;
}

// Remaining private methods go here (deleteRecursive, findMin, etc.)
