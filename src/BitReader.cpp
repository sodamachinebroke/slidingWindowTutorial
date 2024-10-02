//
// Created by hajlektalan on 2024-09-18.
//

#include "BitReader.h"

BitReader::BitReader(const std::string &filename) : inputStream(filename, std::ios::binary), bitBuffer(0), bitCount(0) {
    if (!inputStream) {
        throw std::runtime_error("Unable to open file");
    }
}

bool BitReader::readBit() {
    if (bitCount == 0) {
        if (!inputStream.read(reinterpret_cast<char *>(&bitBuffer), 1)) {
            throw std::runtime_error("End of file reached");
        }
        bitCount = 8;
    }

    bool bit = (bitBuffer >> (bitCount - 1)) & 1;
    --bitCount;
    return bit;
}

uint32_t BitReader::readBits(int numBits) {
    uint32_t result = 0;
    for (int i = 0; i < numBits; ++i) {
        result = (result << 1) | readBit();
    }
    return result;
}

bool BitReader::hasMoreBits() {
    return inputStream.peek() != EOF || bitCount > 0;
}