//
// Created by hajlektalan on 2024-09-18.
//

#ifndef SLIDINGWINDOWTUTORIAL_BITREADER_H
#define SLIDINGWINDOWTUTORIAL_BITREADER_H

#include <string>
#include <cstdint>
#include <fstream>
#include <vector>

class BitReader {
public:
    explicit BitReader(const std::string &filename);

    bool readBit();

    uint32_t readBits(int numBits);

    bool hasMoreBits();

private:
    std::ifstream inputStream;
    uint8_t bitBuffer;
    int bitCount;
};


#endif //SLIDINGWINDOWTUTORIAL_BITREADER_H
