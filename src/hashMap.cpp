//
// Created by hajlektalan on 2024-09-03.
//

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