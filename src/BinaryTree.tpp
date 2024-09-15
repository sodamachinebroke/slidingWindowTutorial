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
    root = _deleteRecursive(root, value);
}

template<typename T>
bool BinaryTree<T>::search(T value) {
    return _searchRecursive(root, value);
}

template<typename T>
void BinaryTree<T>::inorder() {
    _inorderRecursive(root);
    std::cout << std::endl;
}

template<typename T>
void BinaryTree<T>::preorder() {
    _preorderRecursive(root);
    std::cout << std::endl;
}

template<typename T>
void BinaryTree<T>::postorder() {
    _postorderRecursive(root);
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

template<typename T>
void BinaryTree<T>::saveTreeToFile(const std::string &filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    _serialize(root, outFile);
    outFile.close();
    std::cout << "Tree saved to " << filename << std::endl;
}

template<typename T>
void BinaryTree<T>::loadTreeFromFile(const std::string &filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading" << std::endl;
        return;
    }
    root = _deserialize(inFile);
    inFile.close();
    std::cout << "Tree loaded from " << filename << std::endl;
}
