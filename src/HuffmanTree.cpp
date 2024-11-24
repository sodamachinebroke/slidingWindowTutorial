#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "HuffmanTree.h"

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <functional>

void HuffmanTree::buildTree(const std::unordered_map<uint8_t, size_t> &freqMap) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, NodeComparator> pq;

    // Create leaf nodes for each symbol and push into the priority queue
    for (const auto &[symbol, freq]: freqMap) {
        pq.push(new HuffmanNode(symbol, freq));
    }

    // Build the tree
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();
        pq.push(new HuffmanNode(left, right));
    }

    // Set the root
    if (!pq.empty()) {
        root = pq.top();
        pq.pop();
    }
}


void HuffmanTree::serialize(std::ostream &output) const {
    std::function<void(HuffmanNode *)> serializeHelper = [&](HuffmanNode *node) {
        if (!node) return;
        if (!node->left && !node->right) { // Leaf node
            output.put(0x01); // Marker for leaf
            output.put(node->data); // Write the symbol
        } else { // Internal node
            output.put(0x00); // Marker for internal node
            serializeHelper(node->left);
            serializeHelper(node->right);
        }
    };
    serializeHelper(root);
}

void HuffmanTree::deserialize(std::istream &input) {
    std::function<HuffmanNode *()> deserializeHelper = [&]() -> HuffmanNode * {
        char marker = input.get();
        if (marker == 0x01) {
            uint8_t value = input.get();
            return new HuffmanNode(value, 0); // Frequency is not used during deserialization
        } else if (marker == 0x00) {
            HuffmanNode *left = deserializeHelper();
            HuffmanNode *right = deserializeHelper();
            return new HuffmanNode(left, right);
        }
        return nullptr; // Should not reach here
    };

    delete root; // Clean up the old tree
    root = deserializeHelper();
}

HuffmanNode *HuffmanTree::getRoot() const {
    return root;
}

std::string HuffmanTree::getCode(uint8_t byte) const {
    std::string path;
    if (findCode(root, byte, path)) {
        return path;
    }
    throw std::runtime_error("Byte not found in Huffman Tree");
}

bool HuffmanTree::findCode(const HuffmanNode *node, uint8_t byte, std::string &path) const {
    if (!node) {
        return false;
    }

    if (node->isLeaf() && node->data == byte) {
        return true;
    }

    // Explore left subtree
    path.push_back('0');
    if (findCode(node->left, byte, path)) {
        return true;
    }
    path.pop_back();

    // Explore right subtree
    path.push_back('1');
    if (findCode(node->right, byte, path)) {
        return true;
    }
    path.pop_back();

    return false;
}


#pragma clang diagnostic pop