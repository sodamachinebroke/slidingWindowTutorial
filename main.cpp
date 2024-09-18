#include <iostream>
#include <fstream>

#include "src/BinaryTree.h"
#include "src/BitReader.h"


int main() {

    std::string INPUT = "on a rainy day the rain falls softly the rain falls softly and the world is wet the wet world reflects the rain the rain falls softly softly on the wet ground the ground is wet because the rain falls softly the rain falls gently gently on the wet streets the streets are wet and the rain continues the rain continues softly softly and gently gently the rain falls falls softly on the trees the trees are wet from the rain the rain falls softly and gently softly and gently the rain continues to fall the world is wet and the rain is gentle the rain falls gently softly and the wet world reflects the gentle rain";
    /*std::vector<WordInfo> encodedData = HashMap::compressHashMap(INPUT);


    std::cout << "Encoded data: " << std::endl;
    for (const auto &entry: encodedData) {
        std::cout << entry.code << ":" << entry.distance << "%";
    }*/

    BinaryTree tree;

    std::ifstream inputFile("../public/input.dat", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int value;
    while (inputFile.read(reinterpret_cast<char *>(&value), sizeof(int))) {
        tree.insertNode(value);
    }

    try {
        BitReader reader("../public/input.bin");

        while (reader.hasMoreBits()) {
            uint32_t byte = reader.readBits(8);
            auto ucharValue = static_cast<unsigned char>(byte);
            tree.insertNode(ucharValue);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    inputFile.close();

    std::cout << "Postorder traversal: ";
    tree.postorder();

    tree.saveTreeToFile("../public/output.bin");

    BinaryTree newTree;
    try {
        BitReader reader("../public/output.bin");

        while (reader.hasMoreBits()) {
            uint32_t byte = reader.readBits(8);
            auto ucharValue = static_cast<unsigned char>(byte);
            newTree.insertNode(ucharValue);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Postorder traversal: ";
    newTree.postorder();


    /*BinaryTree newTree;
    newTree.loadTreeFromFile("../public/output.bin");

    std::cout << "Postorder traversal: ";
    tree.postorder();

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



    return 0;
}
