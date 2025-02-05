#include "HuffmanCodec.h"

// Generate Huffman codes without explicitly building a tree
void HuffmanCodec::build(const std::string &input) {
    // Step 1: Build frequency table
    std::unordered_map<uint8_t, size_t> frequencyTable;
    for (char ch: input) {
        frequencyTable[static_cast<uint8_t>(ch)]++;
    }

    // Step 2: Priority queue (min-heap) of SymbolNode
    std::priority_queue<SymbolNode, std::vector<SymbolNode>, std::greater<> > pq;
    std::priority_queue<SymbolNode, std::vector<SymbolNode>, std::greater<> > pq2;

    for (const auto &[symbol, frequency]: frequencyTable) {
        pq.push({symbol, frequency, ""});
    }

    // Step 3: Generate codes by merging
    while (pq.size() > 1) {
        SymbolNode left = pq.top();
        pq.pop();
        SymbolNode right = pq.top();
        pq.pop();

        if (left.frequency < right.frequency || (left.frequency == right.frequency && left.symbol < right.symbol)) {
            left.code = "0" + left.code;
            right.code = "1" + right.code;
            if (left.symbol != '\0') { pq2.push(left); }
            if (right.symbol != '\0') { pq2.push(right); }
        } else {
            left.code = "1" + left.code;
            right.code = "0" + right.code;
            if (left.symbol != '\0') { pq2.push(left); }
            if (right.symbol != '\0') { pq2.push(right); }
        }

        SymbolNode combined = {'\0', left.frequency + right.frequency, ""};
        pq.push(combined);
    }

    // Extract codes
    while (!pq2.empty()) {
        SymbolNode current = pq2.top();
        pq2.pop();
        codeMap[current.symbol] = current.code;
        reverseCodeMap[current.code] = current.symbol;
    }
}

// Encode input text into binary and save
void HuffmanCodec::encode(const std::string &input, const std::string &outputFile) {
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << outputFile << std::endl;
        return;
    }

    // Write the size of the code map
    uint16_t mapSize = static_cast<uint16_t>(codeMap.size());
    outFile.write(reinterpret_cast<const char *>(&mapSize), sizeof(mapSize));

    // Write the encoding map: [symbol][length of code][code as bits]
    for (const auto &[symbol, code]: codeMap) {
        uint8_t codeLength = static_cast<uint8_t>(code.size());
        outFile.write(reinterpret_cast<const char *>(&symbol), sizeof(symbol));
        outFile.write(reinterpret_cast<const char *>(&codeLength), sizeof(codeLength));

        uint8_t codeByte = 0;
        uint8_t bitCount = 0;
        for (char bit: code) {
            codeByte = (codeByte << 1) | (bit - '0');
            bitCount++;

            if (bitCount == 8) {
                outFile.write(reinterpret_cast<const char *>(&codeByte), sizeof(codeByte));
                codeByte = 0;
                bitCount = 0;
            }
        }
        if (bitCount > 0) {
            codeByte <<= (8 - bitCount); // Pad remaining bits with 0
            outFile.write(reinterpret_cast<const char *>(&codeByte), sizeof(codeByte));
        }
    }

    // Encode the message itself
    uint8_t buffer = 0;
    uint8_t bitPos = 0;

    for (char ch: input) {
        const std::string &code = codeMap[static_cast<uint8_t>(ch)];
        for (char bit: code) {
            buffer = (buffer << 1) | (bit - '0');
            bitPos++;

            if (bitPos == 8) {
                outFile.write(reinterpret_cast<const char *>(&buffer), sizeof(buffer));
                buffer = 0;
                bitPos = 0;
            }
        }
    }
    if (bitPos > 0) {
        buffer <<= (8 - bitPos); // Pad with 0
        outFile.write(reinterpret_cast<const char *>(&buffer), sizeof(buffer));
    }

    outFile.close();
}

// Decode binary file back into text
void HuffmanCodec::decode(const std::string &inputFile, std::string &output) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << inputFile << std::endl;
        return;
    }

    // Read the size of the code map
    uint16_t mapSize;
    inFile.read(reinterpret_cast<char *>(&mapSize), sizeof(mapSize));

    // Read and reconstruct the encoding map
    reverseCodeMap.clear();
    for (uint16_t i = 0; i < mapSize; ++i) {
        uint8_t symbol, codeLength;
        inFile.read(reinterpret_cast<char *>(&symbol), sizeof(symbol));
        inFile.read(reinterpret_cast<char *>(&codeLength), sizeof(codeLength));

        std::string code;
        uint8_t codeByte = 0;
        while (code.size() < codeLength) {
            inFile.read(reinterpret_cast<char *>(&codeByte), sizeof(codeByte));
            for (int j = 7; j >= 0 && code.size() < codeLength; --j) {
                code.push_back((codeByte & (1 << j)) ? '1' : '0');
            }
        }

        reverseCodeMap[code] = symbol;
    }

    // Decode the binary message
    output.clear();
    std::string currentCode;
    uint8_t byte = 0;
    while (inFile.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        for (int i = 7; i >= 0; --i) {
            currentCode.push_back((byte & (1 << i)) ? '1' : '0');
            if (reverseCodeMap.count(currentCode)) {
                output.push_back(reverseCodeMap[currentCode]);
                currentCode.clear();
            }
        }
    }

    inFile.close();
}

// Utility to print the codes
void HuffmanCodec::printCodes() const {
    for (const auto &[symbol, code]: codeMap) {
        std::cout << "Symbol: " << static_cast<char>(symbol) << ", Code: " << code << '\n';
    }
}
