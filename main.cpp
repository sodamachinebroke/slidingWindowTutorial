#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

// Struct to represent a symbol and its frequency
struct SymbolNode {
    char symbol;
    size_t frequency;
    std::string code;

    // Compare by frequency for the priority queue (min-heap)
    bool operator>(const SymbolNode &other) const {
        return frequency > other.frequency;
    }
};

// Generate Huffman codes without explicitly building a tree
std::unordered_map<char, std::string> generateHuffmanCodes(const std::string &input) {
    // Step 1: Build frequency table
    std::unordered_map<char, size_t> frequencyTable;
    for (char ch: input) {
        frequencyTable[ch]++;
        std::cout << ch << " " << frequencyTable[ch] << std::endl;
    }


    // Step 2: Priority queue (min-heap) of SymbolNode
    std::priority_queue<SymbolNode, std::vector<SymbolNode>, std::greater<>> pq;
    std::priority_queue<SymbolNode, std::vector<SymbolNode>, std::greater<>> pqo;

    // Populate the priority queue with symbols and frequencies
    for (const auto &[symbol, frequency]: frequencyTable) {
        pq.push({symbol, frequency, ""});
    }

    // Step 3: Generate codes by merging
    while (pq.size() > 1) {
        // Get two lowest-frequency nodes
        SymbolNode left = pq.top();
        pq.pop();
        SymbolNode right = pq.top();
        pq.pop();

        // Assign codes: '0' to the left, '1' to the right
        left.code = "0" + left.code;  // Prefix with '0'
        if (left.symbol != '\0')pqo.push(left);
        right.code = "1" + right.code; // Prefix with '1'
        if (right.symbol != '\0')pqo.push(right);

        // Merge into a new node
        SymbolNode combined = {'\0', left.frequency + right.frequency, ""};
        pq.push(combined);
    }

    // Step 4: Extract final codes
    std::unordered_map<char, std::string> codeMap;
    while (!pqo.empty()) {
        SymbolNode current = pqo.top();
        pqo.pop();
        codeMap[current.symbol] = current.code;
    }

    return codeMap;
}

// Main
int main() {
    std::string input = "AAAABBBCCD";
    auto codes = generateHuffmanCodes(input);

    for (const auto &[symbol, code]: codes) {
        std::cout << "Symbol: " << symbol << ", Code: " << code << '\n';
    }

    return 0;
}
