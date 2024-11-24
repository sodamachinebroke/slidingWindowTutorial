#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H

#include <cstdint>
#include <bitset>
#include <memory>


class HuffmanNode {
public:
    uint8_t data;
    size_t frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(uint8_t data, size_t frequency)
            : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    HuffmanNode(HuffmanNode *left, HuffmanNode *right)
            : data(0), frequency(left->frequency + right->frequency), left(left), right(right) {}

    ~HuffmanNode() {
        delete left;
        delete right;
    }


    [[nodiscard]] bool isLeaf() const {
        return !left && !right;
    }
};

#endif //SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
