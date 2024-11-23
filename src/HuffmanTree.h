
#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H

#include "HuffmanNode.h"

#include <memory>
#include <unordered_map>

struct NodeComparator {
    bool operator()(const std::unique_ptr<HuffmanNode> &a, const std::unique_ptr<HuffmanNode> &b) const {
        return a->frequency > b->frequency;
    }
};

class HuffmanTree {
private:
    std::unique_ptr<HuffmanNode> root;

    void buildEncodingMap(const HuffmanNode *node, const std::string &code,
                          std::unordered_map<uint8_t, std::string> &encodingMap) const;

public:
    HuffmanTree() : root(nullptr) {}

    void buildTree(const std::unordered_map<uint8_t, size_t> &freqMap);

    std::unordered_map<uint8_t, std::string> getEncodingMap();

    void serialize(std::ostream &output) const;

    void deserialize(std::istream &input);

    [[nodiscard]] const HuffmanNode *getRoot() const;
};


#endif //SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
