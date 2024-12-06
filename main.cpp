#include "src/HuffmanCodec.h"

int main() {
    HuffmanCodec codec;
    std::string input = "AAAABBBCCD";

    // Build the codes
    codec.build(input);
    codec.printCodes();

    // Encode to binary
    std::string encodedFile = "encoded.bin";
    codec.encode(input, encodedFile);

    // Decode from binary
    std::string decoded;
    codec.decode(encodedFile, decoded);

    std::cout << "Decoded: " << decoded << '\n';

    return 0;
}
