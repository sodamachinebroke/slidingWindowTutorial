#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include "BinaryTree.h"

#ifndef READFILE_H
#define READFILE_H


class ReadFile {
public:
    static int readFromFile(std::size_t chunk_size, const std::string &file, BinaryTree &tree);
};


#endif //READFILE_H
