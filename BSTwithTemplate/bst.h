#pragma once
#include <iostream>
#include <iomanip>

#define MAX_SIZE 100

template<class T>
class BST {
    struct Node {
        T value;
        struct Node* leftChild;
        struct Node* rightChild;
    };
    Node* root;
    void addNode(struct Node** root, struct Node* rootToAdd);
    void deleteNode(struct Node** root, struct Node* rootToDelete);
    bool containsValue(struct Node* node, T value) const;
    void findNodeByValue(struct Node* node, T value, struct Node* &foundNode);
    T minimum(struct Node* root, struct Node*& min);
    void findParentNode(struct Node*& parent, struct Node* child);
    void postorderCleanTree(struct Node** root);
    void preorPrint(struct Node* node) const;
    void trPrint(struct Node* node, int padding) const;
    void fillTreeArray(struct Node* node, T* &values, int &treeSize);
    void createTreeFromArray(T* values, int leftBound, int rightBound, int arrSize);
public:
    BST() : root(nullptr) {};
    explicit BST(T value);
    ~BST();
    void add(T value);
    void del(T value);
    bool contains(T value) const;
    void preorderPrint() const;
    void treePrint() const;
    void changeList(T exValue, T newValue);
    void balanceTree();
};
