#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>

template <typename T>
class Node
{
public:
    T data;
    Node* left;
    Node* right;

    explicit Node(T value);
};

template <typename T>
class BinaryTree
{
public:
    BinaryTree();
    void insertNode(T value);
    void deleteNode(T value);
    bool search(T value);
    void inorder();
    void preorder();
    void postorder();
    void levelOrder();

private:
    Node<T>* root;

    Node<T>* _deleteRecursive(Node<T>* current, T value)
    {
        if (current == nullptr) return nullptr;

        if (current->data == value)
        {
            if (current->left == nullptr && current->right == nullptr)
            {
                delete current;
                return nullptr;
            }
            if (current->left == nullptr)
            {
                Node<T>* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == nullptr)
            {
                Node<T>* temp = current->left;
                delete current;
                return temp;
            }

            Node<T>* successor = _findMin(current->right);
            current->data = successor->data;
            current->right = _deleteRecursive(current->right, successor->data);
        }
        else
        {
            current->left = _deleteRecursive(current->left, value);
            current->right = _deleteRecursive(current->right, value);
        }
        return current;
    }

    Node<T>* _findMin(Node<T>* node)
    {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    bool _searchRecursive(Node<T>* current, T value)
    {
        if (current == nullptr) return false;
        if (current->data == value) return true;
        return _searchRecursive(current->left, value) || _searchRecursive(current->right, value);
    }

    void _inorderRecursive(Node<T>* node)
    {
        if (node != nullptr)
        {
            _inorderRecursive(node->left);
            std::cout << node->data << " ";
            _inorderRecursive(node->right);
        }
    }

    void _preorderRecursive(Node<T>* node)
    {
        if (node != nullptr)
        {
            std::cout << node->data << " ";
            _preorderRecursive(node->left);
            _preorderRecursive(node->right);
        }
    }

    void _postorderRecursive(Node<T>* node)
    {
        if (node != nullptr)
        {
            _postorderRecursive(node->left);
            _postorderRecursive(node->right);
            std::cout << node->data << " ";
        }
    }
};

#include "../BinaryTree.tpp"  // Include the implementation file for templates

#endif  // BINARYTREE_H
