# Sliding window tutorial

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
