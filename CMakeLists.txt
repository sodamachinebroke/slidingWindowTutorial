cmake_minimum_required(VERSION 3.28)
project(slidingWindowTutorial)

# Set the C++ standard to 23 (C++26 is experimental and may not be fully supported)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS)

# Define the BinaryTree library target
add_library(BinaryTree
        src/BinaryTree.cpp
        src/BinaryTree.h
        #        src/Node.h
        #        src/ReadFile.cpp
        #        src/ReadFile.h
        #src/HuffmanCodec.cpp
        #src/HuffmanCodec.h
)

# Create the main executable (slidingWindowTutorial) and link the BinaryTree library
add_executable(slidingWindowTutorial
        main.cpp
)

target_link_libraries(slidingWindowTutorial PRIVATE BinaryTree)

# GoogleTest setup
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create the BinaryTreeTest executable and link the BinaryTree library and gtest
add_executable(BinaryTreeTest tests/BinaryTreeTest.cpp)
target_link_libraries(BinaryTreeTest PRIVATE BinaryTree gtest gtest_main)

add_executable(ReadFileTest tests/ReadFileTest.cpp)
target_link_libraries(ReadFileTest PRIVATE BinaryTree gtest gtest_main)

# Add the test
add_test(NAME BinaryTreeTest COMMAND BinaryTreeTest)
add_test(NAME ReadFileTest COMMAND ReadFileTest)