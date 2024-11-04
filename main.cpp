#include "src/ReadFile.h"

int main() {

    BinaryTree tree;
    ReadFile::readFromFile(256, "../public/input6.bin", tree);
    return 0;
}
