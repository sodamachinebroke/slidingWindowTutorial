# Goal of this documentation

I am learning how to document my progression with my own compression algorithm design.

[//]: # (## Key functions:)

[//]: # ()

[//]: # (- [Split]&#40;commons.md#split&#41;)

[//]: # ()

[//]: # (```c++)

[//]: # (size_t split&#40;const std::string &txt, std::vector<std::string> &strs, char ch&#41;;)

[//]: # (```)

[//]: # ()

[//]: # (Excuse me for pooping all over the place, but here we go)

[//]: # ()

[//]: # (So the basic idea is that there will be a compressor that creates the smallest possible files. The execution is going to)

[//]: # (be done in a number of ways.)

[//]: # ()

[//]: # (I'll list the execution methods quickly:)

# Binary tree

## common binary tree

1. This is done so that there is some base for comparison, but we're here so why not after all.

## Huffman tree

1. This is an advanced form of a binary tree that takes the frequency of every byte, sorts them into a vector
   and builds a binary tree based off that. New methods, contained in this class will only be the tree builder,
   as it will receive a new kind of Node. This thing will supposedly build a more optimized binary tree, but
   let's see how the compressed file will look.

#### Example

- We have the following file, as seen in a HEX-editor: ```64 61 61 62 62 62 62 63 64 64```
  dump: ```daabbbbcdd```
- Let's build a frequency vector (more or less a map, but due to it needing to be sortable, it will now be a
  struct vector):

```c++
'd' => 3
'a' => 2
'b' => 4
'c' => 1
```

Obviously the characters are only represented as characters. In reality they are 8bit long values.

So after we are done with that, let's build a huffman tree:

![htree.svg](images%2Fhtree.svg)

Boom magic

and this will be serialized as the following (according to my ideas):

```
[depth][code][value][code][value][code][value][code][value][encoded bitstream]
[4][1][b][00][d][011][a][010][c][encoded bitstream]
```

Hopefully makes sense

The decompressor will be able to build the tree out of it.

# Length-prefix

i'll look into this

# Byte-stream

This will be more of an n-bit-stream. Basic idea is that codes are stored on equal length fields. From that, it will be
easier to decompress the file. Example will be up soon.