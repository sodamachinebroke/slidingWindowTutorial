#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <fstream>
#include "BitWriter.h"
#include "BitReader.h"
#include "Node.h"


// Binary tree class that stores 'uint8_t' as the data type
class BinaryTree {
public:
    BinaryTree();

    void buildTree();

    void insertNode(uint8_t value);

    void deleteNode(uint8_t value);

    bool search(uint8_t value);

    void inorder();

    void preorder();

    void postorder();

    void levelOrder();

    void saveTreeToFile(const std::string &filename);

    void loadTreeFromFile(const std::string &filename);

private:
    Node *root;

    Node *_deleteRecursive(Node *current, uint8_t value);

    static Node *_findMin(Node *node);

    bool _searchRecursive(Node *current, uint8_t value);

    void _inorderRecursive(Node *node);

    void _preorderRecursive(Node *node);

    void _postorderRecursive(Node *node);

    void _serialize(Node *node, BitWriter &bitWriter);

    Node *_deserialize(BitReader &bitReader);
};

#endif  // BINARYTREE_H
