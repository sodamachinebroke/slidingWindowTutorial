#ifndef SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
#define SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H

#include "Node.h"

class HuffmanNode : public Node {
public:
    int weight;

    explicit HuffmanNode(uint8_t value);
};

#endif //SLIDINGWINDOWTUTORIAL_HUFFMANNODE_H
