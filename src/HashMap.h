//
// Created by hajlektalan on 2024-09-03.
//

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
