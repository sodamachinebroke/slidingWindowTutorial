
#include "HuffmanTree.h"

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <bitset>
#include <functional>

void HuffmanTree::buildEncodingMap(const HuffmanNode *node, const std::string &code,
                                   std::unordered_map<uint8_t, std::string> &encodingMap) const {
    if (!node) return;

    if (node->isLeaf()) {
        encodingMap[node->data] = code;
    } else {
        buildEncodingMap(node->left.get(), code + "0", encodingMap);
        buildEncodingMap(node->right.get(), code + "1", encodingMap);
    }
}


void HuffmanTree::buildTree(const std::unordered_map<uint8_t, size_t> &freqMap) {
    std::priority_queue<std::unique_ptr<HuffmanNode>, std::vector<std::unique_ptr<HuffmanNode>>, NodeComparator> pq;

    // Create leaf nodes for each symbol and push into priority queue
    for (const auto &[symbol, freq]: freqMap) {
        pq.push(std::make_unique<HuffmanNode>(symbol, freq));
    }

    // Build the tree
    while (pq.size() > 1) {
        auto left = std::move(pq.top());
        pq.pop();
        auto right = std::move(pq.top());
        pq.pop();

        pq.push(std::make_unique<HuffmanNode>(std::move(left), std::move(right)));
    }

    // Set the root
    root = std::move(pq.top());
}

void HuffmanTree::serialize(std::ostream &output) const {
    std::function<void(const HuffmanNode *)> serializeHelper = [&](const HuffmanNode *node) {
        if (!node) return;
        if (node->isLeaf()) {
            output.put(0x01);  // Leaf marker
            output.put(node->data);
        } else {
            output.put(0x00);  // Internal node marker
            serializeHelper(node->left.get());
            serializeHelper(node->right.get());
        }
    };

    serializeHelper(root.get());
}

void HuffmanTree::deserialize(std::istream &input) {
    std::function<std::unique_ptr<HuffmanNode>()> deserializeHelper = [&]() -> std::unique_ptr<HuffmanNode> {
        char marker = input.get();
        if (marker == 0x01) {
            uint8_t value = input.get();
            return std::make_unique<HuffmanNode>(value);
        } else if (marker == 0x00) {
            auto left = deserializeHelper();
            auto right = deserializeHelper();
            return std::make_unique<HuffmanNode>(std::move(left), std::move(right));
        }
        return nullptr;  // Should not reach here
    };

    root = deserializeHelper();
}

const HuffmanNode *HuffmanTree::getRoot() const {
    return root.get();
}