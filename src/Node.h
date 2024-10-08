


#ifndef NODE_H
#define NODE_H

#include <cstdint>


class Node {
public:


    Node *left;
    Node *right;
    uint8_t data;

    explicit Node(uint8_t value) : data(value), left(nullptr), right(nullptr) {}
};


#endif //NODE_H
