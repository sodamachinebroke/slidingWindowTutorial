#include "src/ReadFile.h"
//BinaryTree tree;
//ReadFile::readFromFile(256, "../public/input6.bin", tree);
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bitset>
#include <memory>
#include <stdexcept>
#include <cstdint>

struct HuffmanNode {
    uint8_t value;
    uint64_t frequency;
    std::shared_ptr<HuffmanNode> left, right;

    // Constructor for internal nodes
    explicit HuffmanNode(uint64_t freq, std::shared_ptr<HuffmanNode> l = nullptr,
                         std::shared_ptr<HuffmanNode> r = nullptr)
            : value(0), frequency(freq), left(std::move(l)), right(std::move(r)) {}

    // Constructor for leaf nodes
    HuffmanNode(uint8_t val, uint64_t freq) : value(val), frequency(freq) {}

    // Compare nodes by frequency (priority queue)
    bool operator>(const HuffmanNode &other) const {
        return frequency > other.frequency;
    }
};

// Recursive function to build the Huffman codes
void buildHuffmanCodes(const std::shared_ptr<HuffmanNode> &node, const std::string &code,
                       std::unordered_map<uint8_t, std::string> &huffmanCodes) {
    if (!node->left && !node->right) {
        huffmanCodes[node->value] = code; // Leaf node
        return;
    }

    if (node->left) buildHuffmanCodes(node->left, code + "0", huffmanCodes);
    if (node->right) buildHuffmanCodes(node->right, code + "1", huffmanCodes);
}

// Serialize the Huffman tree into a file
void serializeTree(const std::shared_ptr<HuffmanNode> &node, std::ostream &output) {
    if (!node) return;

    if (!node->left && !node->right) {
        // Write marker '1' and the leaf symbol
        char leafMarker = 0b1; // Binary marker for a leaf
        output.put(leafMarker);
        output.put(node->value); // Write symbol as-is
    } else {
        // Write marker '0' for internal node
        char internalMarker = 0b0;
        output.put(internalMarker);
        serializeTree(node->left, output);
        serializeTree(node->right, output);
    }
}


// Deserialize the Huffman tree from a file
std::shared_ptr<HuffmanNode> deserializeTree(std::istream &input) {
    char marker;
    if (!input.get(marker)) return nullptr;

    if (marker & 0b1) {
        // Leaf node: Read the value
        char value;
        input.get(value);
        return std::make_shared<HuffmanNode>(value);
    } else {
        // Internal node
        auto left = deserializeTree(input);
        auto right = deserializeTree(input);
        return std::make_shared<HuffmanNode>(0, left, right); // Internal nodes don't store values
    }
}


// Huffman encode the input data
void huffmanEncode(const std::string &inputFilename, const std::string &outputFilename) {
    // Read the input file
    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Error opening input file.");
    }

    // Count byte frequencies
    std::unordered_map<uint8_t, uint64_t> frequencies;
    std::vector<uint8_t> data(std::istreambuf_iterator<char>(inputFile), {});
    for (uint8_t byte: data) {
        frequencies[byte]++;
    }

    // Build priority queue (min-heap) of Huffman nodes
    auto cmp = [](const std::shared_ptr<HuffmanNode> &a, const std::shared_ptr<HuffmanNode> &b) { return *a > *b; };
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, decltype(cmp)> pq(cmp);

    for (const auto &[byte, freq]: frequencies) {
        pq.push(std::make_shared<HuffmanNode>(byte, freq));
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();
        pq.push(std::make_shared<HuffmanNode>(left->frequency + right->frequency, left, right));
    }

    auto root = pq.top();

    // Generate Huffman codes
    std::unordered_map<uint8_t, std::string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // Serialize the Huffman tree and encoded data
    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Error opening output file.");
    }

    serializeTree(root, outputFile);

    // Write encoded data
    std::string bitString;
    for (uint8_t byte: data) {
        bitString += huffmanCodes[byte];
    }

    // Pad bitString to a multiple of 8
    while (bitString.size() % 8 != 0) {
        bitString += '0';
    }

    for (size_t i = 0; i < bitString.size(); i += 8) {
        uint8_t byte = std::bitset<8>(bitString.substr(i, 8)).to_ulong();
        outputFile.put(byte);
    }

    outputFile.close();
    std::cout << "File successfully Huffman-encoded: " << outputFilename << std::endl;
}

// Huffman decode the input file
void huffmanDecode(const std::string &inputFilename, const std::string &outputFilename) {
    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Error opening input file.");
    }

    // Deserialize the Huffman tree
    auto root = deserializeTree(inputFile);

    // Read encoded data
    std::vector<uint8_t> encodedData(std::istreambuf_iterator<char>(inputFile), {});
    std::string bitString;
    for (uint8_t byte: encodedData) {
        bitString += std::bitset<8>(byte).to_string();
    }

    // Decode the data
    std::ofstream outputFile(outputFilename, std::ios::binary | std::ios::trunc);
    if (!outputFile) {
        throw std::runtime_error("Error opening output file.");
    }

    auto node = root;
    for (char bit: bitString) {
        node = (bit == '0') ? node->left : node->right;

        if (!node->left && !node->right) {
            outputFile.put(node->value);
            node = root;
        }
    }

    outputFile.close();
    std::cout << "File successfully Huffman-decoded: " << outputFilename << std::endl;
}

int main() {
    const std::string inputFilename = "../public/input5.bin";
    const std::string encodedFilename = "../public/temp/encoded.huff";
    const std::string decodedFilename = "../public/output/decoded.bin";

    try {
        huffmanEncode(inputFilename, encodedFilename);
        huffmanDecode(encodedFilename, decodedFilename);
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
