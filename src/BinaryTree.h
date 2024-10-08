#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstdint>
#include <vector>

#include "Node.h"


class BinaryTree {
public:
    BinaryTree();

    uint8_t buildTree(const std::vector<uint8_t> &buffer);

    void insertNode(uint8_t value);

    void deleteNode(uint8_t value);

    //traversal function goes here

private:
    Node *root;

    void serialize(std::vector<uint8_t> buffer);

    void deserialize(std::vector<uint8_t> buffer);
};


#endif //BINARYTREE_H
