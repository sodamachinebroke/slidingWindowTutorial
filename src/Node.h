


#ifndef NODE_H
#define NODE_H
#include <cstdint>


class Node {
public:
    explicit Node(uint8_t value);

    Node *left;
    Node *right;
    uint8_t data;
};


#endif //NODE_H
