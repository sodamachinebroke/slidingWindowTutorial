cmake_minimum_required(VERSION 3.28)
project(slidingWindowTutorial)

set(CMAKE_CXX_STANDARD 26)

add_library(BinaryTree

        src/BinaryTree.cpp
        src/BinaryTree.h
        src/Node.h
)

add_executable(slidingWindowTutorial
        main.cpp
)

target_link_libraries(slidingWindowTutorial PRIVATE BinaryTree)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BinaryTreeTest tests/BinaryTreeTest.cpp)
target_link_libraries(BinaryTreeTest PRIVATE BinaryTree gtest gtest_main)

add_test(NAME BinaryTreeTest COMMAND BinaryTreeTest)