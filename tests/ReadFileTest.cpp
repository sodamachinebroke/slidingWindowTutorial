#include <gtest/gtest.h>

#include "../src/ReadFile.h"

TEST(ReadfileTest, HandlesNoChunk_size) {
    BinaryTree tree;
    int temp = ReadFile::readFromFile(0, "../public/input.bin", tree);
    EXPECT_EQ(temp, 1);
}

TEST(ReadFileTest, HandlesNoFile) {
    BinaryTree tree;
    int temp = ReadFile::readFromFile(256, "", tree);
    EXPECT_EQ(temp, 1);
}

TEST(ReadFileTest, HandlesFile) {
    BinaryTree tree;
    int temp = ReadFile::readFromFile(256, "../public/input.bin", tree);
    EXPECT_EQ(temp, 0);
}

