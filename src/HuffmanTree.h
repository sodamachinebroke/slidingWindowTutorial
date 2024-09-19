//
// Created by hajlektalan on 2024-09-19.
//

#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H

#include <unordered_map>
#include <string>
#include "BitReader.h"
#include <memory>

struct HuffmanNode {
    unsigned char byte;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(unsigned char byte, int frequency) : byte(byte), frequency(frequency), left(nullptr), right(nullptr) {}

    ~HuffmanNode() {
        delete right;
        delete left;
    }
};

struct CompareNode {
    bool operator()(HuffmanNode *const &n1, HuffmanNode *const &n2) {
        return n1->frequency > n2->frequency;
    }
};

class HuffmanTree {
public:
    static HuffmanNode *buildHuffmanTree(const std::unordered_map<unsigned char, int> &frequencies);

    static void generateCodes(HuffmanNode *node, const std::string &code,
                              std::unordered_map<unsigned char, std::string> &codes);

    static void
    saveCompressedFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanNode *root,
                       const std::unordered_map<unsigned char, std::string> &codes);

    HuffmanNode *deserializeTree(BitReader &bitReader);

    void decompressFile(const std::string &compressedFilename, const std::string &outputFilename);
};


#endif //SLIDINGWINDOWTUTORIAL_HUFFMANTREE_H
