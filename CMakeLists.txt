cmake_minimum_required(VERSION 3.28)
project(slidingWindowTutorial)

set(CMAKE_CXX_STANDARD 26)

add_executable(slidingWindowTutorial main.cpp
        src/Commons.cpp
        src/Commons.h
        src/hashMap.cpp
        src/HashMap.h
        src/BinaryTree.h
        src/BitReader.cpp
        src/BitReader.h
        src/BinaryTree.cpp
        src/BitWriter.cpp
        src/BitWriter.h
        src/HuffmanTree.cpp
        src/HuffmanTree.h
        src/Node.h
        src/HuffmanNode.h
        src/Node.cpp
        src/HuffmanNode.cpp
        src/FileReader.cpp
        src/FileReader.h
        src/BinaryTree.cpp
        src/BinaryTree.h
        src/Node.cpp
        src/Node.h
)
