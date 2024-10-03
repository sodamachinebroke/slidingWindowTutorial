#ifndef SLIDINGWINDOWTUTORIAL_NODE_H
#define SLIDINGWINDOWTUTORIAL_NODE_H


#include <cstdint>

class Node {
public:
    uint8_t data;
    Node *left;
    Node *right;

    explicit Node(uint8_t value);
};


#endif //SLIDINGWINDOWTUTORIAL_NODE_H
