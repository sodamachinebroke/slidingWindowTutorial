#include <bits/stdc++.h>

struct MinHeapNode {
    uint8_t data; // One of the input characters
    int freq; // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(const uint8_t data, const int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(const MinHeapNode *l, const MinHeapNode *r) const {
        return (l->freq > r->freq);
    }
};

std::map<uint8_t, std::string> codes;
std::map<uint8_t, int> freq;
std::priority_queue<MinHeapNode *, std::vector<MinHeapNode *>, compare> minHeap;

std::vector<uint8_t> readFromFile(const char *fileName) {
    std::ifstream file(fileName, std::ios::binary);
    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> data;
    data.reserve(fileSize);

    data.insert(data.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return data;
}

void printCodes(const struct MinHeapNode *root, const std::string &str) {
    if (!root)
        return;
    if (root->data != 0)
        std::cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void storeCodes(const struct MinHeapNode *root, const std::string &str) {
    if (root == nullptr)
        return;
    if (root->data != 0)
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}


void HuffmanCodes() {
    struct MinHeapNode *left, *right, *top;
    for (auto &v: freq) minHeap.push(new MinHeapNode(v.first, v.second));

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode(0, left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

void calcFreq(const std::vector<uint8_t> &data) {
    for (uint8_t byte: data) freq[byte]++;
}

std::string decode_file(const struct MinHeapNode *root, const std::string &s) {
    std::string ans;
    const struct MinHeapNode *curr = root;
    for (const char bit: s) {
        curr = (bit == '0') ? curr->left : curr->right;

        if (curr->left == nullptr && curr->right == nullptr) {
            ans += curr->data;
            curr = root;
        }
    }

    return ans;
}

void writeBits(std::ofstream &output, const std::string &bits, uint8_t currentByte, int &bitCount) {
    for (char bit: bits) {
        currentByte = (currentByte << 1) | (bit == '1');
        bitCount++;
        if (bitCount == 8) {
            output.put(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }
}

void flushBits(std::ofstream &output, uint8_t currentByte, int &bitCount) {
    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);
        output.put(currentByte);
        currentByte = 0;
        bitCount = 0;
    }
}

void writeHuffmanTable(std::ofstream &output) {
    uint8_t codeSize = codes.size();
    output.write(reinterpret_cast<const char *>(&codeSize), sizeof(codeSize));

    uint8_t currentByte = 0;
    int bitCount = 0;

    for (const auto &[character, code]: codes) {
        output.put(character);
        uint8_t codeLength = code.size();
        output.put(codeLength);
        writeBits(output, code, currentByte, bitCount);
    }
    flushBits(output, currentByte, bitCount);
}

void writeEncodedData(std::ofstream &output, const std::string &encodedString) {
    uint8_t currentByte = 0;
    int bitCount = 0;

    writeBits(output, encodedString, currentByte, bitCount);
    //flushBits(output, currentByte, bitCount);
}

//This is potentially faulty
void writeBitStringToFile(const std::string &bitString, const std::string &filePath) {
    std::ofstream output(filePath, std::ios::binary); // Open file in binary mode

    if (!output) { return; }


    std::vector<uint8_t> byteBuffer;

    // Process the bit string in chunks of 8 bits
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::string byteString = bitString.substr(i, 8); // Take 8 bits

        // Convert the 8-bit string into a byte
        uint8_t byte = static_cast<uint8_t>(std::bitset<8>(byteString).to_ulong());
        byteBuffer.push_back(byte);
    }

    // Write the byte buffer to the file
    output.write(reinterpret_cast<const char *>(byteBuffer.data()), byteBuffer.size());

    output.close();
    std::cout << "Bit string successfully written to " << filePath << std::endl;
}

uint8_t readCompressed(const char *fileName) {
    std::ifstream file(fileName, std::ios::binary);
    uint8_t mapLength;
    if (!file) return 0xFF;
    file.read(reinterpret_cast<char *>(&mapLength), 1);
    return mapLength;
}

int main() {
    std::vector<uint8_t> data = readFromFile("../public/input.bin");
    std::string encodedString;

    calcFreq(data);
    HuffmanCodes();
    std::cout << "Character With their frequencies:\n";
    for (auto &v: freq) std::cout << static_cast<int>(v.first) << ": " << v.second << std::endl;

    std::cout << std::endl << "Huffman Codes:" << std::endl;

    // create the invertedMap
    std::vector<std::pair<std::string, uint8_t> > invertedMap;
    for (const auto &[key,value]: codes) {
        invertedMap.emplace_back(value, key);
    }

    //sort invertedMap by code length
    std::ranges::sort(invertedMap, [](const auto &a, const auto &b) {
        return a.first.length() < b.first.length();
    });

    //-- HEADER START --
    std::string headerString;

    //Count code lengths and build the length-counts map
    std::map<size_t, size_t> length_counts;
    for (const auto &[value, key]: invertedMap) {
        length_counts[value.length()]++;
    }

    //Write the header information to the header string
    for (const auto &[length, count]: length_counts) {
        //encode count
        headerString += std::bitset<8>(count).to_string();
        //encode length
        headerString += std::bitset<8>(length).to_string();

        //add code and byte value
        for (const auto &[code, byte]: invertedMap) {
            if (code.length() == length) {
                headerString += std::bitset<8>(byte).to_string();
                headerString += code;
            }
        }
    }
    // -- HEADER END --

    //Compress data
    for (uint8_t byte: data) {
        encodedString += codes[byte];
    }

    std::string completeBitString = headerString + encodedString;

    //invertedMap contents
    std::cout << "invertedMap contents: " << std::endl;
    for (const auto &[value,key]: invertedMap) {
        std::cout << value << " " << static_cast<int>(key) << std::endl;
    }

    std::cout << "Writing encoded data to file: " << std::endl;
    writeBitStringToFile(completeBitString, "../public/output/input.bin.comp");

    /*for (auto &v: codes) std::cout << static_cast<int>(v.first) << ": " << v.second << std::endl;
    encodedString += std::bitset<8>{codes.size()}.to_string();

    //for (std::pair<uint8_t, std::string> byte: codes) {
    //    encodedString += std::bitset<8>{byte.first}.to_string() + byte.second;
    //}

    for (const auto &[value, key]: invertedMap) {
        //count the vector and organize by length
        length_counts[value.length()]++;
    }

    for (const auto &[value, key]: invertedMap) {
        //output the vector onto the console
        std::cout << "{" << value << ", " << static_cast<int>(key) << "}" << std::endl;
    }*/

    /*for (uint8_t byte: data) //supposedly this is for filling the string with the data, so this is the content
        encodedString += codes[byte];


    //std::cout << std::endl << "Encoded Huffman data:" << std::endl << encodedString << std::endl;

    std::cout << "Writing encoded data to a file..." << std::endl;
    writeBitStringToFile(encodedString, "../public/output/input.bin.comp");

    const uint8_t length = readCompressed("../public/output/input.bin.comp");
    std::cout << "First byte is: " << static_cast<int>(length) << std::endl;*/
    //
    //
    // // Function call
    // std::string decodedString = decode_file(minHeap.top(), encodedString);
    // std::cout << "\nDecoded Huffman Data:\n" << decodedString << std::endl;
    //
    // for (char byte: decodedString) std::cout << static_cast<int>(static_cast<uint8_t>(byte)) << ' ';
    // std::cout << std::endl;
    return 0;
}
