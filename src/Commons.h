#include <vector>
#include <string>
#include <unordered_map>

#ifndef COMMONS_H
#define COMMONS_H

class Commons {
public:

    static size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);

    static std::unordered_map<unsigned char, int> calculateFrequencies(const std::string &filename);

};

#endif //COMMONS_H
