#include "FileReader.h"

#include <fstream>
#include <iterator>
#include <vector>

//returns buffer
std::vector<uint8_t> FileReader::ReadFile(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(file), {}};
}
