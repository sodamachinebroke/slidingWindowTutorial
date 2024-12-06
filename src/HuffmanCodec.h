#ifndef HUFFMAN_CODEC_H
#define HUFFMAN_CODEC_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

// Struct to represent a symbol and its frequency
struct SymbolNode {
    uint8_t symbol; // Symbol being encoded
    size_t frequency; // Frequency of the symbol
    std::string code; // Huffman code for the symbol

    bool operator>(const SymbolNode &other) const {
        return frequency > other.frequency; // Min-heap comparison
    }
};

class HuffmanCodec {
private:
    std::unordered_map<uint8_t, std::string> codeMap; // Huffman encoding table
    std::unordered_map<std::string, uint8_t> reverseCodeMap; // Reverse table for decoding

public:
    // Generate Huffman codes from input
    void build(const std::string &input);

    // Encode a message and save as binary file
    void encode(const std::string &input, const std::string &outputFile);

    // Decode a binary file
    void decode(const std::string &inputFile, std::string &output);

    // Utility to print codes
    void printCodes() const;
};

#endif // HUFFMAN_CODEC_H
