#include <iostream>
#include <fstream>
#include <unordered_map>

#include "src/BinaryTree.h"
#include "src/BitReader.h"
#include "src/HuffmanTree.h"


std::unordered_map<uint8_t, int> buildFrequencyTable(const std::string &inputFilename) {
    std::ifstream inFile(inputFilename, std::ios::binary);
    std::unordered_map<uint8_t, int> frequencies;
    uint8_t byte;

    while (inFile.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        frequencies[byte]++;
    }

    return frequencies;
}

std::pair<uint8_t, int> findMaxEntry(const std::unordered_map<uint8_t, int> &frequencies) {
    std::pair<uint8_t, int> maxEntry = std::make_pair(0, 0);

    for (auto frequency: frequencies) {
        if (frequency.second > maxEntry.second) {
            maxEntry = std::make_pair(frequency.first, frequency.second);
        }
    }

    return maxEntry;
}

int main() {

    //std::string INPUT = "on a rainy day the rain falls softly the rain falls softly and the world is wet the wet world reflects the rain the rain falls softly softly on the wet ground the ground is wet because the rain falls softly the rain falls gently gently on the wet streets the streets are wet and the rain continues the rain continues softly softly and gently gently the rain falls falls softly on the trees the trees are wet from the rain the rain falls softly and gently softly and gently the rain continues to fall the world is wet and the rain is gentle the rain falls gently softly and the wet world reflects the gentle rain";
    /*std::vector<WordInfo> encodedData = HashMap::compressHashMap(INPUT);


    std::cout << "Encoded data: " << std::endl;
    for (const auto &entry: encodedData) {
        std::cout << entry.code << ":" << entry.distance << "%";
    }*/

    //BinaryTree tree;

    /*std::ifstream inputFile("../public/input.dat", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int value;
    while (inputFile.read(reinterpret_cast<char *>(&value), sizeof(int))) {
        tree.insertNode(value);
    }

    try {
        BitReader reader("../public/input3.bin");

        while (reader.hasMoreBits()) {
            uint8_t byte = reader.readBits(8);
            auto ucharValue = static_cast<uint8_t>(byte);
            std::cout << static_cast<uint8_t>(byte) << std::endl;
            tree.insertNode(ucharValue);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Postorder traversal: ";
    tree.postorder();

    tree.saveTreeToFile("../public/output3.bin");*/

    /* BinaryTree newTree;
     newTree.loadTreeFromFile("../public/output3.bin");

     std::cout << "Postorder traversal: ";
     tree.postorder();*/

    /*std::cout << "Inorder traversal: ";
    tree.inorder();

    std::cout << "Preorder traversal: ";
    tree.preorder();



    std::cout << "Level order traversal: ";
    tree.levelOrder();

    std::cout << "Searching for 7: " << (tree.search(7) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 6: " << (tree.search(6) ? "Found" : "Not Found") << std::endl;

    tree.deleteNode(3);
    std::cout << "Inorder traversal after removing 3: ";
    tree.inorder();

    */

    std::string inputFilename = "../public/input3.bin";
    std::string outputFilename = "../public/output3comp.bin";

    std::unordered_map<uint8_t, int> frequencies = buildFrequencyTable(inputFilename);
    for (auto x: frequencies) {
        std::cout << x.first << " -> " << x.second << std::endl;
    }

    std::cout << "Highest frequency key - value: " << findMaxEntry(frequencies).first << " -> "
              << findMaxEntry(frequencies).second << std::endl;

    HuffmanNode *root = HuffmanTree::buildHuffmanTree(frequencies);

    std::unordered_map<uint8_t, std::string> huffmanCodes;
    HuffmanTree::generateCodes(root, "", huffmanCodes);

    HuffmanTree::saveCompressedFile(inputFilename, outputFilename, root, huffmanCodes);

    delete root;

    std::cout << "File compressed successfully!" << std::endl;
    return 0;
}
