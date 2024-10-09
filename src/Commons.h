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
