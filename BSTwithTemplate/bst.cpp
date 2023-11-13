//
// Created by hvoro on 03.11.2023.
//

#include "BST.h"

template<class T>
BST<T>::BST(T value) {
    struct Node initialiseNode(value);
    this->root = &initialiseNode;
}

template<class T>
T BST<T>::minimum(BST::Node *root, BST::Node *&min) {
    if (root->leftChild == nullptr) {
        min = root;
        return root->value;
    }
    return this->minimum(root->leftChild, min);
}

template<class T>
void BST<T>::addNode(BST::Node **root, BST::Node *rootToAdd) {
    if (*root == nullptr) {
        *root = rootToAdd;
        return;
    }
    if ((*root)->value > rootToAdd->value) {
        this->addNode(&(*root)->leftChild, rootToAdd);
    } else {
        this->addNode(&(*root)->rightChild, rootToAdd);
    }
}

template<class T>
void BST<T>::add(T value) {
    if (this->containsValue(this->root, value)) {
        std::cout << "This value is already in tree! Try again!" << std::endl;
        return;
    }
    struct Node *nodeToAdd = new Node;
    nodeToAdd->value = value;
    nodeToAdd->leftChild = nullptr;
    nodeToAdd->rightChild = nullptr;
    this->addNode(&this->root, nodeToAdd);
}

template<class T>
bool BST<T>::contains(T value) const {
    return containsValue(this->root, value);
}

template<class T>
bool BST<T>::containsValue(struct Node *node, T value) const {
    if (node == nullptr)
        return false;
    if (node->value == value)
        return true;
    if (node->value > value)
        return this->containsValue(node->leftChild, value);
    else if (node->value < value)
        return this->containsValue(node->rightChild, value);
}

template<class T>
void BST<T>::findNodeByValue(Node *node, T value, Node *&foundNode) {
    if (node == nullptr)
        return;
    if (node->value == value) {
        foundNode = node;
        return;
    }
    if (node->value > value)
        this->findNodeByValue(node->leftChild, value, foundNode);
    else if (node->value < value)
        this->findNodeByValue(node->rightChild, value, foundNode);
}

template<class T>
void BST<T>::findParentNode(BST::Node *&parent, BST::Node *child) {
    if (this->root == child)
        return;
    struct Node *temp = this->root;
    while (temp != child) {
        parent = temp;
        if (temp->value > child->value)
            temp = temp->leftChild;
        else temp = temp->rightChild;
    }
}

template<class T>
void BST<T>::deleteNode(BST::Node **root, BST::Node *rootToDelete) {
    //  default case: it's the root
    if (*root == rootToDelete) {
        if ((*root)->rightChild && (*root)->leftChild) {
            struct Node *change = (*root)->leftChild;
            while (change->rightChild != nullptr) {
                change = change->rightChild;
            }
            change->rightChild = (*root)->rightChild;
            change->leftChild = (*root)->leftChild;
            struct Node *temp = (*root);
            *root = change;
            delete temp;
            return;
        } else if ((*root)->rightChild || (*root)->leftChild) {
            struct Node *child = (*root)->leftChild ? (*root)->leftChild : (*root)->rightChild;
            struct Node *temp = (*root);
            *root = child;
            delete temp;
            return;
        } else if (*root == nullptr) {
            delete *root;
            *root = nullptr;
            return;
        }
    }
    struct Node *parent;
    this->findParentNode(parent, rootToDelete);
    //  first case: hasn't any child
    if (rootToDelete->rightChild == nullptr && rootToDelete->leftChild == nullptr) {
        if (rootToDelete == parent->leftChild) {
            delete parent->leftChild;
            parent->leftChild = nullptr;
        } else {
            delete parent->rightChild;
            parent->rightChild = nullptr;
        }
    }
        //  second case: has both children
    else if (rootToDelete->rightChild && rootToDelete->leftChild) {
        struct Node *rightSubtreeMinimum;
        T rightSubtreeMinValue = this->minimum(rootToDelete->rightChild, rightSubtreeMinimum);
        deleteNode(root, rightSubtreeMinimum);
        delete rightSubtreeMinimum;
        rootToDelete->value = rightSubtreeMinValue;
    }
        //  third case: has only one child
    else if (rootToDelete->rightChild || rootToDelete->leftChild) {
        struct Node *child = rootToDelete->leftChild ? rootToDelete->leftChild : rootToDelete->rightChild;
        struct Node *temp = rootToDelete;
        if (child == rootToDelete->leftChild) parent->leftChild = temp->leftChild;
        else parent->rightChild = temp->rightChild;
        delete temp;
    }
}

template<class T>
void BST<T>::del(T value) {
    struct Node *deleted = nullptr;
    this->findNodeByValue(this->root, value, deleted);
    if (deleted) {
        this->deleteNode(&this->root, deleted);
    } else {
        std::cout << "There's no element with this value" << std::endl;
        return;
    }
}

template<class T>
void BST<T>::postorderCleanTree(BST::Node** root) {
    if (*root == nullptr) {
        return;
    }
    this->postorderCleanTree(&(*root)->leftChild);
    this->postorderCleanTree(&(*root)->rightChild);
    delete *root;
    *root = nullptr;
}

template<class T>
BST<T>::~BST() {
    this->postorderCleanTree(&this->root);
}

template<class T>
void BST<T>::preorderPrint() const {
    this->preorPrint(this->root);
}

template<class T>
void BST<T>::treePrint() const {
    this->trPrint(this->root, 0);
}

template<class T>
void BST<T>::changeList(T exValue, T newValue) {
    this->del(exValue);
    this->add(newValue);
}

template<class T>
void BST<T>::preorPrint(BST::Node* node) const {
    if (node == nullptr) {
        return;
    }
    std::cout << node->value << ", ";
    this->preorPrint(node->leftChild);
    this->preorPrint(node->rightChild);
}

template<class T>
void BST<T>::trPrint(BST::Node* node, int padding) const {
    if (node == nullptr) {
        return;
    }
    trPrint(node->rightChild, padding + 1);
    for (int i = 0; i < padding; i++) {
        std::cout << "   ";
    }
    std::cout << node->value << std::endl;
    trPrint(node->leftChild, padding + 1);
}

template<class T>
void BST<T>::fillTreeArray(struct Node* node, T* &values, int &treeSize) {
    if (node == nullptr)
        return;
    this->fillTreeArray(node->leftChild, values, treeSize);
    values[treeSize++] = node->value;
    this->fillTreeArray(node->rightChild, values, treeSize);
}

template<class T>
void BST<T>::balanceTree() {
    T *treeArray = new T();
    int treeSize = 0;
    this->fillTreeArray(this->root, treeArray, treeSize);
    int medium = treeSize / 2;
    this->postorderCleanTree(&this->root);
    this->createTreeFromArray(treeArray, 1, treeSize, treeSize);
}

template<class T>
void BST<T>::createTreeFromArray(T* values, int leftBound, int rightBound, int arrSize) {
    if (arrSize == 1) {
        this->add(values[leftBound - 1]);
        return;
    }
    if (arrSize == 2) {
        this->add(values[leftBound - 1]);
        this->add(values[rightBound - 1]);
        return;
    }
    int medium = leftBound + arrSize / 2;
    if (arrSize % 2 == 0) --medium;
    this->add(values[medium - 1]);
    this->createTreeFromArray(values, leftBound, medium - 1, arrSize % 2 == 0 ? arrSize / 2 - 1 : arrSize / 2 );
    this->createTreeFromArray(values, medium + 1, rightBound, arrSize / 2);
}