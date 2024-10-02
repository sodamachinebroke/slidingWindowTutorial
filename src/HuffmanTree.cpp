//
// Created by hajlektalan on 2024-09-19.
//

#include "HuffmanTree.h"
#include "BitWriter.h"

#include <unordered_map>
#include <queue>
#include <string>
#include <fstream>
#include <functional>

HuffmanNode *HuffmanTree::buildHuffmanTree(const std::unordered_map<uint8_t, int> &frequencies) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNode> minHeap;
    for (const auto &[byte, frequency]: frequencies) {
        minHeap.push(new HuffmanNode(byte, frequency));
    }

    while (minHeap.size() > 1) {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();
        HuffmanNode *right = minHeap.top();
        minHeap.pop();

        auto *parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);

    }

    return minHeap.top();

}

void HuffmanTree::generateCodes(HuffmanNode *node, const std::string &code,
                                std::unordered_map<uint8_t, std::string> &codes) {
    if (!node) return;
    //wtf is a leaf node
    if (!node->left && !node->right) {
        codes[node->byte] = code;
    }

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);


}

void
HuffmanTree::saveCompressedFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanNode *root,
                                const std::unordered_map<uint8_t, std::string> &codes) {
    std::ifstream inFile(inputFilename, std::ios::binary);
    BitWriter bitWriter(outputFilename);

    std::function<void(HuffmanNode *)> serializeTree = [&](HuffmanNode *node) {
        if (!node) {
            bitWriter.writeBit(false);
            return;
        }

        bitWriter.writeBit(true);
        if (!node->left && !node->right) {
            bitWriter.writeByte(node->byte);
        }

        serializeTree(node->left);
        serializeTree(node->right);
    };

    serializeTree(root);

    uint8_t byte;

    while (inFile.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        const std::string &code = codes.at(byte);

        for (char bit: code) {
            bitWriter.writeBit(bit == '1');
        }
    }

}

HuffmanNode *HuffmanTree::deserializeTree(BitReader &bitReader) {

    if (!bitReader.readBit()) { return nullptr; }

    if (bitReader.readBit()) {
        uint8_t byte = bitReader.readBits(8);
        return new HuffmanNode(byte, 0);
    }

    HuffmanNode *node = new HuffmanNode('\0', 0);
    node->left = deserializeTree(bitReader);
    node->right = deserializeTree(bitReader);
    return node;

}

void HuffmanTree::decompressFile(const std::string &compressedFilename, const std::string &outputFilename) {
    BitReader bitReader(compressedFilename);
    HuffmanNode *root = deserializeTree(bitReader);

    std::ofstream outFile(outputFilename, std::ios::binary);

    HuffmanNode *currentNode = root;
    while (bitReader.hasMoreBits()) {
        bool bit = bitReader.readBit();
        if (bit) {
            currentNode = currentNode->right;
        } else {
            currentNode = currentNode->left;
        }

        if (!currentNode->left && !currentNode->right) {
            outFile.write(reinterpret_cast<char *> (&currentNode->byte), sizeof(currentNode->byte));
            currentNode = root;
        }
    }
    outFile.close();
}
