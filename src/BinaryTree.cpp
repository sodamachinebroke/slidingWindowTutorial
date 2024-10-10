#include "BinaryTree.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

BinaryTree::BinaryTree() : root(nullptr) {
}


uint8_t BinaryTree::buildTree(const std::vector<uint8_t> &buffer) {
    if (buffer.empty()) return 0;

    root = new Node(buffer[0]);

    if (buffer.size() == 1) return 1;

    std::queue<Node *> nodeQueue;
    nodeQueue.push(root);

    size_t index = 1;
    uint8_t depth = 0;

    while (!nodeQueue.empty()) {
        const size_t levelSize = nodeQueue.size();
        ++depth;

        for (size_t i = 0; i < levelSize; ++i) {
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

        if (depth == 255)break;
    }
    return depth;
}

