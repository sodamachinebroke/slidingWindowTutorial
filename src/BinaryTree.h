#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstdint>
#include <vector>

#include "Node.h"


class BinaryTree {
public:
    BinaryTree();

    uint8_t buildTree(const std::vector<uint8_t> &buffer);

private:
    Node *root;
};


#endif //BINARYTREE_H
