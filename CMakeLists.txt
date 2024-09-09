cmake_minimum_required(VERSION 3.28)
project(slidingWindowTutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(slidingWindowTutorial main.cpp
        src/commons.cpp
        src/header/commons.h
        src/hashMap.cpp
        src/header/hashMap.h
        src/header/BinaryTree.h
        src/BinaryTree.tpp
        src/BinaryTree.tpp
)
