


#include "BinaryTree.h"

#include <iostream>
#include <vector>
#include <queue>

BinaryTree::BinaryTree() : root(nullptr) {
}


uint8_t BinaryTree::buildTree(const std::vector<uint8_t> &buffer) {
    if (buffer.empty()) {
        std::cout << "Buffer size is less than 1." << std::endl;
        return 0; // no tree
    }

    root = new Node(buffer[0]);

    std::queue<Node *> nodeQueue;
    nodeQueue.push(root);

    size_t index = 1;
    uint8_t depth = 0;

    while (index < buffer.size()) {
        std::queue<Node *>::size_type levelSize = nodeQueue.size();

        for (std::queue<Node *>::size_type i = 0; levelSize && index < buffer.size(); ++i) {
            Node *current = nodeQueue.front();
            nodeQueue.pop();

            if (index < buffer.size()) {
                current->left = new Node(buffer[index++]);
                nodeQueue.push(current->left);
            }

            if (index < buffer.size()) {
                current->right = new Node(buffer[index++]);
                nodeQueue.push(current->right);
            }

        }
        ++depth;

        if (depth == 255) {
            break;
        }
    }
    return depth; //robot wrote this.
}

