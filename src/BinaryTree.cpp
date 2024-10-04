


#include "BinaryTree.h"

#include <iostream>
#include <ostream>

BinaryTree::BinaryTree() : root(nullptr) {
}


uint8_t BinaryTree::buildTree(const std::vector<uint8_t> &buffer, std::vector<Node *> &nodes) {
    if (buffer.empty()) {
        std::cout << "Buffer size is less than 1." << std::endl;
        return 0; // no tree
    }


    for (const uint8_t i: buffer) {
        auto newNode = new Node(i);
        if (root == nullptr) {
            root = newNode;
        }

        nodes.push_back(root);

        while (!nodes.empty()) {
            Node *current = nodes[i];

            if (current->left == nullptr) {
                current->left = newNode;
                nodes.push_back(newNode);
            } else {
                nodes.push_back(current->left);
            }

            if (current->right == nullptr) {
                current->right = newNode;
                nodes.push_back(newNode);
            } else {
                nodes.push_back(current->right);
            }
        }
    }

    return nodes.size();
}

