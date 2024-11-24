#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H

#include <cstdint>
#include <bitset>
#include <memory>


class HuffmanNode {
public:
    uint8_t data;                // Symbol
    size_t frequency;            // Frequency of the symbol
    HuffmanNode *left;           // Left child
    HuffmanNode *right;          // Right child

    // Constructor for a leaf node
    HuffmanNode(uint8_t data, size_t frequency)
            : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    // Constructor for an internal node
    HuffmanNode(HuffmanNode *left, HuffmanNode *right)
            : data(0), frequency(left->frequency + right->frequency), left(left), right(right) {}

    ~HuffmanNode() {
        delete left;
        delete right;
    }

    // Check if this is a leaf node
    [[nodiscard]] bool isLeaf() const {
        return !left && !right;
    }
};

#endif //SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
