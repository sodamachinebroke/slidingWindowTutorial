#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <fstream>
#include "BitWriter.h"
#include "BitReader.h"

// Node structure for the binary tree
class Node {
public:
    unsigned char data;
    Node *left;
    Node *right;

    explicit Node(unsigned char value);
};

// Binary tree class that stores 'unsigned char' as the data type
class BinaryTree {
public:
    BinaryTree();

    void insertNode(unsigned char value);

    void deleteNode(unsigned char value);

    bool search(unsigned char value);

    void inorder();

    void preorder();

    void postorder();

    void levelOrder();

    void saveTreeToFile(const std::string &filename);

    void loadTreeFromFile(const std::string &filename);

private:
    Node *root;

    Node *_deleteRecursive(Node *current, unsigned char value);

    static Node *_findMin(Node *node);

    bool _searchRecursive(Node *current, unsigned char value);

    void _inorderRecursive(Node *node);

    void _preorderRecursive(Node *node);

    void _postorderRecursive(Node *node);

    void _serialize(Node *node, BitWriter &bitWriter);

    Node *_deserialize(BitReader &bitReader);
};

#endif  // BINARYTREE_H
