#ifndef FILEREADER_H
#define FILEREADER_H
#include <filesystem>
#include <vector>


class FileReader {
public:
    static std::vector<uint8_t> ReadFile(const std::filesystem::path &path);
};


#endif //FILEREADER_H
