# Recycle bin

These codes are technically still usable, but are not in use, so instead of deleting everything, i am resorting to sort
of put them in a recycle bin instead. Might reuse later, might not. Either way, they will exist here.

# Commons

The old Commons class provides a string manipulation algorithm that splits a string into a vector of strings by a
delimiter. The second function is used for creating a Huffman Tree and that one calculates the frequencies of words in a
file i think.

## Commons.h

```c++
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

#ifndef COMMONS_H
#define COMMONS_H

class Commons {
public:

    static size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

    static std::unordered_map<uint8_t, int> calculateFrequencies(const std::string &filename);

};

#endif //COMMONS_H
```

## Commons.cpp

```c++
#include "Commons.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cstdint>

size_t Commons::split(const std::string &txt, std::vector<std::string> &strs, char ch) {

    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();

}

std::unordered_map<uint8_t, int> Commons::calculateFrequencies(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    std::unordered_map<uint8_t, int> frequencies;
    uint8_t byte;

    while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        frequencies[byte]++;
    }

    return frequencies;
}

```

# HashMap

This one uses a hash map to technically compress a string into smaller values. It works, it just has no meaningful
function.

## HashMap.h

```c++
#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>

struct WordInfo { // this can definitely be done without this
    int code;
    int distance;
};

class HashMap {
public:
    static std::vector<WordInfo> compressHashMap(const std::basic_string<char> &INPUT);
};

#endif //HASHMAP_H
```

## HashMap.cpp

```c++
#include <vector>
#include <unordered_map>
#include "HashMap.h"
#include "Commons.h"


std::vector<WordInfo> HashMap::compressHashMap(const std::basic_string<char> &INPUT) {
    std::vector<std::basic_string<char> > raw_data;

    Commons::split(INPUT, raw_data, ' ');

    std::unordered_map<std::basic_string<char>, int> wordCodeMap;
    std::vector<WordInfo> encodedData;

    int currentCode = 1;
    std::unordered_map<std::basic_string<char>, int> firstOccurrence;

    for (int i = 0; i < raw_data.size(); ++i) {
        const std::basic_string<char> &word = raw_data[i];
        if (firstOccurrence.find(word) == firstOccurrence.end()) {
            firstOccurrence[word] = i;
            wordCodeMap[word] = currentCode++;

            encodedData.push_back({wordCodeMap[word], 0});
        } else {
            int distance = i - firstOccurrence[word];
            encodedData.push_back({wordCodeMap[word], distance});
        }
    }
    return encodedData;
}
```

## buildFrequencyTable

This was in the main function, but it builds a frequency table for a Huffman Tree

```c++
std::unordered_map<uint8_t, int> buildFrequencyTable(const std::string &inputFilename) {
    std::ifstream inFile(inputFilename, std::ios::binary);
    std::unordered_map<uint8_t, int> frequencies;
    uint8_t byte;

    while (inFile.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        frequencies[byte]++;
    }

    return frequencies;
}
```

## findMaxEntry

This was also implemented in the main function and it finds the highest frequency entry. Used for creating a Huffman
Tree once again.

```c++
std::pair<uint8_t, int> findMaxEntry(const std::unordered_map<uint8_t, int> &frequencies) {
    std::pair<uint8_t, int> maxEntry = std::make_pair(0, 0);

    for (auto frequency: frequencies) {
        if (frequency.second > maxEntry.second) {
            maxEntry = std::make_pair(frequency.first, frequency.second);
        }
    }

    return maxEntry;
}
```

```c++
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <iomanip>

std::vector<uint8_t> readBinaryFile(const std::string &filename) {
std::ifstream file(filename, std::ios::binary);
if (!file) throw std::runtime_error("Error opening file: " + filename);
return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

void runLengthEncode(const std::vector<uint8_t> &data, const std::string &filename) {
std::ofstream file(filename, std::ios::binary);
if (!file) return;

std::vector<std::pair<uint8_t, uint32_t>> encodedData;

for (size_t i = 0; i < data.size();) {
uint8_t value = data[i];
uint32_t count = 1;

while (i + count < data.size() && data[i + count] == value) ++count;

encodedData.emplace_back(value, count);
i += count;
}

for (const auto &[value, count]: encodedData) {
file.write(reinterpret_cast<const char *>(&value), sizeof(uint8_t));
file.write(reinterpret_cast<const char *>(&count), sizeof(uint32_t));
}

file.close();

std::cout << "Data written to: " << filename << std::endl;
}

void runLengthDecode(const std::string &filename, std::vector<uint8_t> &decodedData) {
std::ifstream file(filename, std::ios::binary);
if (!file) return;
decodedData.clear();

uint8_t value;
uint32_t count;

while (file.read(reinterpret_cast<char *>(&value), sizeof(uint8_t)) &&
file.read(reinterpret_cast<char *>(&count), sizeof(uint32_t))) {
for (uint32_t i = 0; i < count; ++i) decodedData.push_back(value);
}

file.close();
std::cout << "Run-Length Decoded data read from " << filename << std::endl;
}
```

```c++
 const std::string infile = "../public/movie.mp4";
const std::string outfile = "../public/rle_movie.bin";
try {

std::vector<uint8_t> data = readBinaryFile(infile);
runLengthEncode(data, outfile);

// std::vector<uint8_t> decodedData;
//runLengthDecode(outfile, decodedData);

// Verify the result
/*std::cout << "Original Data: ";
for (uint8_t value: data) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) value << " ";
}
std::cout << "\nDecoded Data: ";
for (uint8_t value: decodedData) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) value << " ";
}
std::cout << std::endl;*/
} catch (const std::exception &e) {
std::cerr << "Error: " << e.what() << std::endl;

}
```

# This might be recyclable

It builds a binary tree out of the code, but does it wrong. I decided to ditch the binary tree and use hash chains
instead.

```c++
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
```