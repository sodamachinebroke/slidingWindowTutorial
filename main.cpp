#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "src/header/commons.h"

struct WordInfo {
    int code;
    int distance;
};

int main() {
    std::string INPUT = "on a rainy day the rain falls softly the rain falls softly and the world is wet the wet world reflects the rain the rain falls softly softly on the wet ground the ground is wet because the rain falls softly the rain falls gently gently on the wet streets the streets are wet and the rain continues the rain continues softly softly and gently gently the rain falls falls softly on the trees the trees are wet from the rain the rain falls softly and gently softly and gently the rain continues to fall the world is wet and the rain is gentle the rain falls gently softly and the wet world reflects the gentle rain";
    std::vector<std::string> raw_data;

    Commons::split(INPUT, raw_data, ' ');

    std::unordered_map<std::string, int> wordCodeMap;
    std::vector<WordInfo> encodedData;

    int currentCode = 1;
    std::unordered_map<std::string, int> firstOccurrence;

    for (int i = 0; i < raw_data.size(); ++i) {
        const std::string &word = raw_data[i];
        if (firstOccurrence.find(word) == firstOccurrence.end()) {
            firstOccurrence[word] = i;
            wordCodeMap[word] = currentCode++;

            encodedData.push_back({wordCodeMap[word], 0});
        } else {
            int distance = i - firstOccurrence[word];
            encodedData.push_back({wordCodeMap[word], distance});
        }
    }

    std::cout << "Encoded data: " << std::endl;
    for (const auto &entry: encodedData) {
        std::cout << entry.code << ":" << entry.distance << "%";
    }

    return 0;
}
