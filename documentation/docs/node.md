Basic node storage class

Has left and right Node pointers, which creates a recursive chain. In this recursive chain, every node has a value or
`data`. This is used to store the binary value, aka a `byte` or in this case `uint8_t`.
<details>
<summary style="cursor: pointer; user-select: none">Node</summary>
```c++
class Node {
public:

    Node *left;
    Node *right;
    uint8_t data;

    explicit Node(uint8_t value) : data(value), left(nullptr), right(nullptr) {}

};

```
</details>

