# Sliding window tutorial

# [Documentation](https://sodamachinebroke.github.io/slidingWindowTutorial/)

This repository serves as more of a collection of functions and algorithms that show my journey across the compression
hellscape.

My language of choice is C++26, which should serve plenty well, along with its Inline Assembly feature. I am going to
primarily use the JetBrains CLion IDE and the goal of this is to experiment with different approaches to file
compression.

So far I have made a function that uses entropy coding with a dynamic dictionary to compress a string.

## Planned functions

- Binary tree instead of a hashmap for storing the code
- File handling, byte compression
- Compression using Inline Assembly, as it provides a much faster run time


Inline Assembly proved irrelevant, as g++ translates code into a much better machine code than I could ever write.

Moreover, i have managed to store things in binary trees, but cannot compress, which is pretty bad and kind of against the whole idea lol
I have created a topic. Idk what that's called, help
You can find it [here](documentation/topic.md)

Also a very basic UML diagram regarding the Huffman tree and binary tree

![UML diagram](documentation/uml1.svg)

Google Benchmarks for microbenchmarking

