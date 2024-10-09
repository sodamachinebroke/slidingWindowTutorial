#include <gtest/gtest.h>
#include "../src/BinaryTree.h"

#include <cstdint>

TEST(BinaryTreeTest, HandlesEmptyBuffer) {
    BinaryTree tree;
    std::vector<uint8_t> buffer = {};
    uint8_t depth = tree.buildTree(buffer);
    EXPECT_EQ(depth, 0);
}

TEST(BinaryTreeTest, HandlesSingleElement) {
    BinaryTree tree;
    std::vector<uint8_t> buffer = {42};
    uint8_t depth = tree.buildTree(buffer);
    EXPECT_EQ(depth, 1);
}

TEST(BinaryTreeTest, HandlesThreeElements) {
    BinaryTree tree;
    std::vector<uint8_t> buffer = {42, 13, 69};
    uint8_t depth = tree.buildTree(buffer);
    EXPECT_EQ(depth, 2);
}

TEST(BinaryTreeTest, HandlesLargerBuffer) {
    BinaryTree tree;
    std::vector<uint8_t> buffer = {1, 2, 3, 4, 5, 6, 7};
    uint8_t depth = tree.buildTree(buffer);
    EXPECT_EQ(depth, 3);
}

TEST(BinaryTreeTest, HandlesMaxDepth) {
    BinaryTree tree;
    std::vector<uint8_t> buffer(255, 1);
    uint8_t depth = tree.buildTree(buffer);
    EXPECT_EQ(depth, 255);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}