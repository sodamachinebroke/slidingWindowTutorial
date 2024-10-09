I can recycle this hopefully

## buildFrequencyTable

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