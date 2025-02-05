# This essentially is the second step in compression

It reads the file in chunks (preferably 2^x) and outputs a vector of numbers that later form the base for the binary
tree's builder.

## How it works

We will go into detail about how it works, step by step. (Step =/= line, step = code block)

```c++
if (chunk_size < 1) {
std::cerr << "chunk_size is less than 1" << std::endl;
return 1;
}
```

This checks whether the specified chunk size is actually more than 1, as a 0-length chunk doesn't exist.

```c++
if (!input.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
}
```

This checks whether there is an actual file.

```c++
std::vector<char> buffer(chunk_size);
std::unordered_set<char> unique_bytes;
```

It creates a `char` buffer and another `char` buffer. One of them stores the values read in a chunk and the other one
will store the unique bytes in the buffer.

```c++
while (input.read(buffer.data(), static_cast<std::streamsize>(chunk_size)) || input.gcount() > 0) {
    auto bytes_read = static_cast<std::size_t>(input.gcount());
        
    for (std::size_t i = 0; i < bytes_read; ++i) {
    unique_bytes.insert(buffer[i]);
    }
}
```

As long as there is still bytes to read, it will read them and create a `size_t` variable that stores the length
it needs to input into the `unique_bytes` vector. Which it will later return with.

```c++
input.close();

    std::vector<uint8_t> unique_vector(unique_bytes.begin(), unique_bytes.end());
    std::sort(unique_vector.begin(), unique_vector.end());
    std::cout << "Unique bytes in the file" << std::endl;

    int i = 0;
    for (uint8_t byte: unique_vector) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>( static_cast<uint8_t>(byte))
                  << " ";
        ++i;
    }
    uint8_t depth = tree.buildTree(unique_vector);
    std::cout << std::endl << "Size of unique_vector: " << unique_vector.size() << std::endl << "Tree depth: "
              << static_cast<int>(depth)
              << std::endl << "Tree built!" << std::endl;
        return 0;

}
```

Closes input file and then sorts the vector, prints it onto the screen, then builds a binary tree that is in the first
argument of the function.

<details>
<summary style="cursor: pointer; user-select: none"> readFromFile.h</summary>
```c++
#ifndef READFILE_H
#define READFILE_H

class ReadFile {
public:
static int readFromFile(std::size_t chunk_size, const std::string &file, BinaryTree &tree);
};

#endif //READFILE_H

```
</details>

<details>
<summary style="cursor: pointer; user-select: none"> readFromFile.cpp</summary>
```c++
int ReadFile::readFromFile(const std::size_t chunk_size, const std::string &file, BinaryTree &tree) {
if (chunk_size < 1) {
std::cerr << "chunk_size is less than 1" << std::endl;
return 1;
}

    std::vector<char> buffer(chunk_size); // Buffer for reading chunks
    std::unordered_set<char> unique_bytes;

    // Open file in binary mode
    std::ifstream input(file, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // Read file in chunks
    while (input.read(buffer.data(), static_cast<std::streamsize>(chunk_size)) || input.gcount() > 0) {
        auto bytes_read = static_cast<std::size_t>(input.gcount()); // Number of bytes read in the last chunk

        for (std::size_t i = 0; i < bytes_read; ++i) {
            unique_bytes.insert(buffer[i]);
        }
    }

    input.close();

    std::vector<uint8_t> unique_vector(unique_bytes.begin(), unique_bytes.end());
    std::sort(unique_vector.begin(), unique_vector.end());
    std::cout << "Unique bytes in the file" << std::endl;

    int i = 0;
    for (uint8_t byte: unique_vector) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>( static_cast<uint8_t>(byte))
                  << " ";
        ++i;
    }
    uint8_t depth = tree.buildTree(unique_vector);
    std::cout << std::endl << "Size of unique_vector: " << unique_vector.size() << std::endl << "Tree depth: "
              << static_cast<int>(depth)
              << std::endl << "Tree built!" << std::endl;

    return 0;

}

```

</details>