#include <iostream>

class Node {
    public:
        int value;
        Node* leftChild, * rightChild, * parent;
        Node();
        Node(int v);
        Node(int v, Node* p);
};

class BinarySearchTree {
    private:
        Node* root;
        Node* HiddenInsert(Node* node, int value);
        Node* HiddenDelete(Node* node, int value);
        void HiddenDisplay(Node* node);
        Node* HiddenFindMin(Node* node);
        Node* HiddenFindMax(Node* node);
    public:
        BinarySearchTree();
        void Insert(int value);
        void Delete(int value);
        void Display();
        int FindMin();
        int FindMax();
};

Node::Node() {
    value = 0;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v) {
    value = v;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v, Node* p) {
    value = v;
    parent = p;
    leftChild = rightChild =  nullptr;
}

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}
Node* BinarySearchTree::HiddenInsert(Node* node, int value) {
    if(node == nullptr) {
        return new Node(value);
    }

    if(value < node->value) {
        node->leftChild = HiddenInsert(node->leftChild, value);
    }
    if(value > node->value) {
        node->rightChild = HiddenInsert(node->rightChild, value);
    }
    return node;
}
Node* BinarySearchTree::HiddenFindMin(Node* node) {
    if(node->leftChild == nullptr) {
        return node;
    }
    else {
        return HiddenFindMin(node->leftChild);
    }
}
Node* BinarySearchTree::HiddenFindMax(Node* node) {
    if(node->rightChild == nullptr) {
        return node;
    }
    else {
        return HiddenFindMax(node->rightChild);
    }
}
Node* BinarySearchTree::HiddenDelete(Node* node, int value) {
    if(node->value == value) {
        if(node->leftChild == nullptr && node->rightChild == nullptr) {
            delete node;
            return nullptr;
        }
        if(node->leftChild == nullptr) {
            Node* shouldReturn = node->rightChild;
            delete node;
            return shouldReturn;
        }
        if(node->rightChild == nullptr) {
            Node* shouldReturn = node->leftChild;
            delete node;
            return shouldReturn;
        }
        Node* succNode = HiddenFindMin(node->rightChild);
        node->value = succNode->value;
        node->rightChild = HiddenDelete(node->rightChild, succNode->value);
        return node;
    }
    if(value < node->value) {
        node->leftChild = HiddenDelete(node->leftChild, value);
    }
    else {
        node->rightChild = HiddenDelete(node->rightChild, value);
    }
    return node;
}
void BinarySearchTree::HiddenDisplay(Node* node) {
    if(node->leftChild != nullptr) {
        HiddenDisplay(node->leftChild);
    }
    std::cout << node->value << ' ';
    if(node->rightChild != nullptr) {
        HiddenDisplay(node->rightChild);
    }
    return;
}
void BinarySearchTree::Insert(int value) {
    root = HiddenInsert(root, value);
    return;
}
void BinarySearchTree::Delete(int value) {
    root = HiddenDelete(root, value);
    return;
}
void BinarySearchTree::Display() {
    HiddenDisplay(root);
    return;
}
int BinarySearchTree::FindMin() {
    return HiddenFindMin(root)->value;
}
int BinarySearchTree::FindMax() {
    return HiddenFindMax(root)->value;
}