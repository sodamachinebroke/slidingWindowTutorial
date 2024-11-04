#include "ReadFile.h"
#include "BinaryTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <cstdint>
#include <algorithm>


int
ReadFile::readFromFile(const std::size_t chunk_size, const std::string &file, BinaryTree &tree) {// Chunk size in bytes
    if (chunk_size < 1) {
        std::cerr << "chunk_size is less than 1" << std::endl;
        return 1;
    }


    std::vector<char> buffer(chunk_size); // Buffer for reading chunks
    std::unordered_set<char> unique_bytes;

    // Open file in binary mode
    std::ifstream input(file, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // Read file in chunks
    while (input.read(buffer.data(), static_cast<std::streamsize>(chunk_size)) || input.gcount() > 0) {
        auto bytes_read = static_cast<std::size_t>(input.gcount()); // Number of bytes read in the last chunk

        for (std::size_t i = 0; i < bytes_read; ++i) {
            unique_bytes.insert(buffer[i]);
        }
    }

    input.close();

    std::vector<uint8_t> unique_vector(unique_bytes.begin(), unique_bytes.end());
    std::sort(unique_vector.begin(), unique_vector.end());
    std::cout << "Unique bytes in the file" << std::endl;

    int i = 0;
    for (uint8_t byte: unique_vector) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>( static_cast<uint8_t>(byte))
                  << " ";
        ++i;
    }
    uint8_t depth = tree.buildTree(unique_vector);
    std::cout << std::endl << "Size of unique_vector: " << unique_vector.size() << std::endl << "Tree depth: "
              << static_cast<int>(depth)
              << std::endl << "Tree built!" << std::endl;

    return 0;
}