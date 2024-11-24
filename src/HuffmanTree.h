
#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H

#include "HuffmanNode.h"

#include <memory>
#include <unordered_map>

struct NodeComparator {
    bool operator()(const HuffmanNode *lhs, const HuffmanNode *rhs) const {
        return lhs->frequency > rhs->frequency; // Lower frequency gets higher priority
    }
};


#include <queue>
#include <unordered_map>
#include <iostream>

class HuffmanTree {
private:
    HuffmanNode *root; // Root of the Huffman Tree

public:
    HuffmanTree() : root(nullptr) {}

    ~HuffmanTree() {
        delete root; // Automatically deletes the entire tree
    }

    void buildTree(const std::unordered_map<uint8_t, size_t> &freqMap);

    void serialize(std::ostream &output) const;

    void deserialize(std::istream &input);

    // Helper for debugging: prints the tree
    void printTree() const { printTreeHelper(root, ""); }

    [[nodiscard]] HuffmanNode *getRoot() const;

    [[nodiscard]] std::string getCode(uint8_t byte) const;

private:
    void printTreeHelper(HuffmanNode *node, const std::string &prefix) const {
        if (!node) return;
        if (!node->left && !node->right) {
            std::cout << prefix << "Leaf: " << (int) node->data << " (" << node->frequency << ")\n";
        } else {
            std::cout << prefix << "Internal Node (" << node->frequency << ")\n";
        }
        printTreeHelper(node->left, prefix + "  ");
        printTreeHelper(node->right, prefix + "  ");
    }


    bool findCode(const HuffmanNode *node, uint8_t byte, std::string &path) const;
};


#endif //SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
