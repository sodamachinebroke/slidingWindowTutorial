#include <iostream>
#include <fstream>

#include "src/header/BinaryTree.h"


int main() {

    std::string INPUT = "on a rainy day the rain falls softly the rain falls softly and the world is wet the wet world reflects the rain the rain falls softly softly on the wet ground the ground is wet because the rain falls softly the rain falls gently gently on the wet streets the streets are wet and the rain continues the rain continues softly softly and gently gently the rain falls falls softly on the trees the trees are wet from the rain the rain falls softly and gently softly and gently the rain continues to fall the world is wet and the rain is gentle the rain falls gently softly and the wet world reflects the gentle rain";
    /*std::vector<WordInfo> encodedData = hashMap::compressHashMap(INPUT);


    std::cout << "Encoded data: " << std::endl;
    for (const auto &entry: encodedData) {
        std::cout << entry.code << ":" << entry.distance << "%";
    }*/

    BinaryTree<int> tree;

    std::ifstream inputFile("../public/input.dat", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int value;
    while (inputFile.read(reinterpret_cast<char *>(&value), sizeof(int))) {
        tree.insertNode(value);
    }

    inputFile.close();

    std::cout << "Preorder traversal: ";
    tree.preorder();

    tree.saveTreeToFile("../public/output.dat");

    BinaryTree<int> newTree;
    newTree.loadTreeFromFile("../public/output.dat");

    std::cout << "Preorder traversal: ";
    newTree.preorder();

    /*std::cout << "Inorder traversal: ";
    tree.inorder();

    std::cout << "Preorder traversal: ";
    tree.preorder();

    std::cout << "Postorder traversal: ";
    tree.postorder();

    std::cout << "Level order traversal: ";
    tree.levelOrder();

    std::cout << "Searching for 7: " << (tree.search(7) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 6: " << (tree.search(6) ? "Found" : "Not Found") << std::endl;

    tree.deleteNode(3);
    std::cout << "Inorder traversal after removing 3: ";
    tree.inorder();*/

    return 0;
}
