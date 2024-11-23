#include "HuffmanCodec.h"

void HuffmanCodec::build(const std::unordered_map<uint8_t, size_t> &freqMap) {
    tree.buildTree(freqMap);
    encodingMap = tree.getEncodingMap();
}

std::vector<bool> HuffmanCodec::encode(const std::vector<uint8_t> &message) const {
    std::vector<bool> encodedBits;
    for (uint8_t byte: message) {
        const std::string &code = encodingMap.at(byte);
        for (char bit: code) {
            encodedBits.push_back(bit == '1');
        }
    }
    return encodedBits;
}

std::vector<uint8_t> HuffmanCodec::decode(const std::vector<bool> &encodedBits) const {
    std::vector<uint8_t> decodedMessage;
    const HuffmanNode *current = tree.getRoot();

    for (bool bit: encodedBits) {
        current = bit ? current->right.get() : current->left.get();

        if (current->isLeaf()) {
            decodedMessage.push_back(current->data);
            current = tree.getRoot();
        }
    }

    return decodedMessage;
}

void HuffmanCodec::serializeTree(std::ostream &output) const {
    tree.serialize(output);
}

void HuffmanCodec::deserializeTree(std::istream &input) {
    tree.deserialize(input);
    encodingMap = tree.getEncodingMap();
}
