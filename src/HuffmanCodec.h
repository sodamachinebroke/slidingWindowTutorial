#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANCODEC_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANCODEC_H

#include "HuffmanTree.h"
#include <vector>

class HuffmanCodec {
private:
    HuffmanTree tree;

public:
    void build(const std::unordered_map<uint8_t, size_t> &freqMap);

    std::vector<bool> encode(const std::vector<uint8_t> &message) const;

    std::vector<uint8_t> decode(const std::vector<bool> &encodedBits) const;

    void serializeTree(std::ostream &output) const;

    void deserializeTree(std::istream &input);
};

#endif // SLIDINGWINDOWTUTORIAL_HUFFMANCODEC_H
