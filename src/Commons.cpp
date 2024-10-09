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

