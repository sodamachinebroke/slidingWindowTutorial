# Recycle bin

These codes are technically still usable, but are not in use, so instead of deleting everything, i am resorting to sort
of put them in a recycle bin instead. Might reuse later, might not. Either way, they will exist here.

# Commons

The old Commons class provides a string manipulation algorithm that splits a string into a vector of strings by a
delimiter. The second function is used for creating a Huffman Tree and that one calculates the frequencies of words in a
file i think.

## Commons.h

```c++
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
```

## Commons.cpp

```c++
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

```

# HashMap

This one uses a hash map to technically compress a string into smaller values. It works, it just has no meaningful
function.

## HashMap.h

```c++
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
```

## HashMap.cpp

```c++
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
```

## buildFrequencyTable

This was in the main function, but it builds a frequency table for a Huffman Tree

```c++
std::unordered_map<uint8_t, int> buildFrequencyTable(const std::string &inputFilename) {
    std::ifstream inFile(inputFilename, std::ios::binary);
    std::unordered_map<uint8_t, int> frequencies;
    uint8_t byte;

    while (inFile.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        frequencies[byte]++;
    }

    return frequencies;
}
```

## findMaxEntry

This was also implemented in the main function and it finds the highest frequency entry. Used for creating a Huffman
Tree once again.

```c++
std::pair<uint8_t, int> findMaxEntry(const std::unordered_map<uint8_t, int> &frequencies) {
    std::pair<uint8_t, int> maxEntry = std::make_pair(0, 0);

    for (auto frequency: frequencies) {
        if (frequency.second > maxEntry.second) {
            maxEntry = std::make_pair(frequency.first, frequency.second);
        }
    }

    return maxEntry;
}
```

```c++
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <iomanip>

std::vector<uint8_t> readBinaryFile(const std::string &filename) {
std::ifstream file(filename, std::ios::binary);
if (!file) throw std::runtime_error("Error opening file: " + filename);
return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

void runLengthEncode(const std::vector<uint8_t> &data, const std::string &filename) {
std::ofstream file(filename, std::ios::binary);
if (!file) return;

std::vector<std::pair<uint8_t, uint32_t>> encodedData;

for (size_t i = 0; i < data.size();) {
uint8_t value = data[i];
uint32_t count = 1;

while (i + count < data.size() && data[i + count] == value) ++count;

encodedData.emplace_back(value, count);
i += count;
}

for (const auto &[value, count]: encodedData) {
file.write(reinterpret_cast<const char *>(&value), sizeof(uint8_t));
file.write(reinterpret_cast<const char *>(&count), sizeof(uint32_t));
}

file.close();

std::cout << "Data written to: " << filename << std::endl;
}

void runLengthDecode(const std::string &filename, std::vector<uint8_t> &decodedData) {
std::ifstream file(filename, std::ios::binary);
if (!file) return;
decodedData.clear();

uint8_t value;
uint32_t count;

while (file.read(reinterpret_cast<char *>(&value), sizeof(uint8_t)) &&
file.read(reinterpret_cast<char *>(&count), sizeof(uint32_t))) {
for (uint32_t i = 0; i < count; ++i) decodedData.push_back(value);
}

file.close();
std::cout << "Run-Length Decoded data read from " << filename << std::endl;
}
```

```c++
 const std::string infile = "../public/movie.mp4";
const std::string outfile = "../public/rle_movie.bin";
try {

std::vector<uint8_t> data = readBinaryFile(infile);
runLengthEncode(data, outfile);

// std::vector<uint8_t> decodedData;
//runLengthDecode(outfile, decodedData);

// Verify the result
/*std::cout << "Original Data: ";
for (uint8_t value: data) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) value << " ";
}
std::cout << "\nDecoded Data: ";
for (uint8_t value: decodedData) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) value << " ";
}
std::cout << std::endl;*/
} catch (const std::exception &e) {
std::cerr << "Error: " << e.what() << std::endl;

}
```