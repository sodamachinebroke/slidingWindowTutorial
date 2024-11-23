#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H

#include <cstdint>
#include <bitset>
#include <memory>


class HuffmanNode {
public:
    uint8_t data;
    size_t frequency;
    std::unique_ptr<HuffmanNode> left;
    std::unique_ptr<HuffmanNode> right;

    // Constructor for leaf nodes
    explicit HuffmanNode(uint8_t value, size_t freq = 0)
            : data(value), frequency(freq), left(nullptr), right(nullptr) {}

    // Constructor for internal nodes
    HuffmanNode(std::unique_ptr<HuffmanNode> leftChild, std::unique_ptr<Node> rightChild)
            : data(0), frequency(leftChild->frequency + rightChild->frequency),
              left(std::move(leftChild)), right(std::move(rightChild)) {}

    // Check if this is a leaf node
    [[nodiscard]] bool isLeaf() const {
        return !left && !right;
    }
};

#endif //SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
