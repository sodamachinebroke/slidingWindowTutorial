//
// Created by hajlektalan on 2024-09-18.
//

#include "BinaryTree.h"
#include "BitReader.h"
#include "BitWriter.h"

Node::Node(unsigned char value) : data(value), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::insertNode(unsigned char value) {
    Node *newNode = new Node(value);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            return;
        } else {
            q.push(current->left);
        }
        if (current->right == nullptr) {
            current->right = newNode;
            return;
        } else {
            q.push(current->right);
        }
    }
}

Node *BinaryTree::_deleteRecursive(Node *current, unsigned char value) {
    if (current == nullptr) return nullptr;

    if (current->data == value) {
        if (current->left == nullptr && current->right == nullptr) {
            delete current;
            return nullptr;
        }
        if (current->left == nullptr) {
            Node *temp = current->right;
            delete current;
            return temp;
        }
        if (current->right == nullptr) {
            Node *temp = current->left;
            delete current;
            return temp;
        }

        Node *successor = _findMin(current->right);

        current->data = successor->data;
        current->right = _deleteRecursive(current->right, successor->data);
    } else {
        current->left = _deleteRecursive(current->left, value);
        current->right = _deleteRecursive(current->right, value);
    }
    return current;
}

Node *BinaryTree::_findMin(Node *node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

bool BinaryTree::_searchRecursive(Node *current, unsigned char value) {
    if (current == nullptr) return false;
    if (current->data == value) return true;
    return _searchRecursive(current->left, value) || _searchRecursive(current->right, value);
}

bool BinaryTree::search(unsigned char value) {
    return _searchRecursive(root, value);
}

void BinaryTree::_inorderRecursive(Node *node) {
    if (node != nullptr) {
        _inorderRecursive(node->left);
        std::cout << static_cast<int> (node->data) << " ";
        _inorderRecursive(node->right);
    }
}

void BinaryTree::inorder() {
    _inorderRecursive(root);
    std::cout << std::endl;
}

void BinaryTree::_preorderRecursive(Node *node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        _preorderRecursive(node->left);
        _preorderRecursive(node->right);
    }
}

void BinaryTree::preorder() {
    _preorderRecursive(root);
    std::cout << std::endl;
}

void BinaryTree::_postorderRecursive(Node *node) {
    if (node != nullptr) {
        _postorderRecursive(node->left);
        _postorderRecursive(node->right);
        std::cout << static_cast<int>(node->data) << " ";
    }
}

void BinaryTree::postorder() {
    _postorderRecursive(root);
    std::cout << std::endl;
}


void BinaryTree::levelOrder() {
    if (root == nullptr) return;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *current = q.front();
        q.pop();

        std::cout << static_cast<int>(current->data) << " ";

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    std::cout << std::endl;
}

void BinaryTree::_serialize(Node *node, BitWriter &bitWriter) {
    if (!node) {
        bitWriter.writeBit(0);
        return;
    }
    bitWriter.writeBit(1);
    bitWriter.writeByte(node->data);
    _serialize(node->left, bitWriter);
    _serialize(node->right, bitWriter);
}

Node *BinaryTree::_deserialize(BitReader &bitReader) {
    if (!bitReader.readBit()) {
        return nullptr;
    }

    unsigned char value = bitReader.readBits(8);
    Node *node = new Node(value);
    node->left = _deserialize(bitReader);
    node->right = _deserialize(bitReader);
    return node;
}

void BinaryTree::saveTreeToFile(const std::string &filename) { //TODO fix
    BitWriter bitWriter(filename);

    _serialize(root, bitWriter);
    std::cout << "Tree save to " << filename << " using bit-level serialization." << std::endl;
}


void BinaryTree::loadTreeFromFile(const std::string &filename) { //TODO fix
    BitReader bitReader(filename);

    root = _deserialize(bitReader);
    std::cout << "Tree loaded from " << filename << " using bit-level deserialization." << std::endl;
}