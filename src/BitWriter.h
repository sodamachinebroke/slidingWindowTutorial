//
// Created by hajlektalan on 2024-09-18.
//

#ifndef SLIDINGWINDOWTUTORIAL_BITWRITER_H
#define SLIDINGWINDOWTUTORIAL_BITWRITER_H

#include <fstream>

class BitWriter {

public:
    explicit BitWriter(const std::string &filename) : outFile(filename, std::ios::binary), bitBuffer(0), bitCount(0) {
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing");
        }
    }

    ~BitWriter() {
        if (bitCount > 0) {
            flush();
        }
        outFile.close();
    }

    void writeBit(bool bit) {
        bitBuffer = (bitBuffer << 1) | bit;
        bitCount++;
        if (bitCount == 8) {
            flush();
        }
    }

    void writeByte(uint8_t byte) {
        for (int i = 7; i >= 0; --i) {
            writeBit((byte >> i) & 1);
        }
    }

private:
    std::ofstream outFile;
    uint8_t bitBuffer;
    int bitCount;

    void flush() {
        outFile.write(reinterpret_cast<char *>(&bitBuffer), 1);
        bitBuffer = 0;
        bitCount = 0;
    }
};


#endif //SLIDINGWINDOWTUTORIAL_BITWRITER_H
