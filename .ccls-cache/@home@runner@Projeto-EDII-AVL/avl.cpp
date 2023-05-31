#include <iostream>
#include <string>
#include <vector>



class Node {
public:
    ProgramaNetFlix data;
    int height;
    Node* left;
    Node* right;

    Node(ProgramaNetFlix data)
        : data(data), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* insertNode(Node* node, ProgramaNetFlix data);

public:
    AVLTree() : root(nullptr) {}
    void insert(ProgramaNetFlix data);
};

int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* AVLTree::insertNode(Node* node, ProgramaNetFlix data) {
    if (node == nullptr) {
        return new Node(data);
    }

    if (data.getId() < node->data.getId()) {
        node->left = insertNode(node->left, data);
    } else if (data.getId() > node->data.getId()) {
        node->right = insertNode(node->right, data);
    } else {
        // Handle case where the node already exists (if needed)
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (data.getId() < node->left->data.getId()) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (balanceFactor < -1) {
        if (data.getId() > node->right->data.getId()) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

void AVLTree::insert(ProgramaNetFlix data) {
    root = insertNode(root, data);
}
