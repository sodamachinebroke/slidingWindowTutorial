## This class is used for building the binary tree that stores the bytes

Main functions:

### `BinaryTree()`

 ```c++
 BinaryTree::BinaryTree() : root(nullptr) {
 }
```

Constructor for the class, this is where `root` is being stored. `root` is the root of the b-tree. Self-explanatory.

### `buildTree(const std::vector<uint8_t> &buffer)`

This function serves as the backbone of the whole program.

Asks for the buffer vector, which consists of bytes. It builds these bytes into a tree. Unfortunately not a very
efficient tree.
Returns the depth of said tree.

<details>
<summary style="cursor: pointer; user-select: none"> buildTree</summary>
```c++
uint8_t BinaryTree::buildTree(const std::vector<uint8_t> &buffer) {
    if (buffer.empty()) return 0;

    root = new Node(buffer[0]);

    if (buffer.size() == 1) return 1;

    std::queue<Node *> nodeQueue;
    nodeQueue.push(root);

    size_t index = 1;
    uint8_t depth = 0;

    while (!nodeQueue.empty()) {
        const size_t levelSize = nodeQueue.size();
        ++depth;

        for (size_t i = 0; i < levelSize; ++i) {
            Node *current = nodeQueue.front();
            nodeQueue.pop();

            if (index < buffer.size()) {
                current->left = new Node(buffer[index++]);
                nodeQueue.push(current->left);
            }
            if (index < buffer.size()) {
                current->right = new Node(buffer[index++]);
                nodeQueue.push(current->right);
            }
        }

        if (depth == 255)break;
    }
    return depth;

}

```

</details>

