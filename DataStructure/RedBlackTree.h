#include <iostream>

namespace String {

class Node {
    public:
        int value, blackHeight;
        bool isRed;
        Node* parent, * child[2];
        Node();
        Node(int v);
        Node(int v, Node* p);
};
Node::Node() {
    value = 0, blackHeight = 0;
    isRed = false;
    parent = nullptr, child[0] = child[1] = nullptr;
}
Node::Node(int v) {
    value = v, blackHeight = 2;
    isRed = false;
    parent = nullptr, child[0] = child[1] = nullptr;
}
Node::Node(int v, Node* p) {
    value = v, blackHeight = 1;
    isRed = true;
    parent = p, child[0] = child[1] = nullptr;
}

class RedBlackTree {
    private:
        const bool LEFT=0, RIGHT=1;
        Node* root;
        void Rotate(Node* node, bool toRight);
        void Fixup(Node* node);
        void HiddenDisplay(Node* node);
        Node* Successor(Node* node);
        Node* HiddenDelete(Node* node, int value);
    public:
        RedBlackTree();
        void Insert(int value);
        void Delete(int value);
        void Display();
};

RedBlackTree::RedBlackTree() {
    root = nullptr;
}
/*void RedBlackTree::LeftRotate(Node* node) {
    Node* tempNode = node->child[RIGHT];

    tempNode->child[LEFT]->parent = node;
    node->child[RIGHT] = tempNode->child[LEFT];

    tempNode->child[LEFT] = node;
    node->parent = tempNode;
    
    tempNode->parent = node->parent;
    if(tempNode->parent == nullptr) {
        root = tempNode;
    }
    else {
        tempNode->parent->child[node == node->parent->child[1]] = tempNode;
    }
}*/
void RedBlackTree::Rotate(Node* node, bool toRight) {
    Node* tempNode = node->child[!toRight];
    if(tempNode->child[toRight] != nullptr) {
        tempNode->child[toRight]->parent = node;
    }
    node->child[!toRight] = tempNode->child[toRight];
    
    tempNode->parent = node->parent;
    if(tempNode->parent == nullptr) {
        root = tempNode;
    }
    else {
        tempNode->parent->child[node == node->parent->child[RIGHT]] = tempNode;
    }

    tempNode->child[toRight] = node;
    node->parent = tempNode;
}
void RedBlackTree::Fixup(Node* node) {
    while(node->parent != nullptr && node->parent->isRed) {
        /*if(node->parent = node->parent->parent->child[LEFT]) {
            Node* uncleNode = node->parent->child[RIGHT];
            if(uncleNode->isRed) {
                node->parent->isRed = uncleNode->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            }
            else {
                if(node = node->parent->child[RIGHT]) {
                    node = node->parent;
                    Rotate(node, LEFT);
                }
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                Rotate(node->parent->parent, RIGHT);
            }
        }*/
        bool isLeft = (node->parent == node->parent->parent->child[LEFT]);
        
        Node* uncleNode = node->parent->parent->child[isLeft];
        if(uncleNode != nullptr && uncleNode->isRed) {
            node->parent->isRed = uncleNode->isRed = false;
            node->parent->parent->isRed = true;
            node = node->parent->parent;
        }
        else {
            if(node == node->parent->child[isLeft]) {
                node = node->parent;
                Rotate(node, !isLeft);
            }
            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            Rotate(node->parent->parent, isLeft);
        }
    }
    root->isRed = false;
}
void RedBlackTree::HiddenDisplay(Node* node) {
    if(node == nullptr) {
        return;
    }
    HiddenDisplay(node->child[LEFT]);
    std::cout << node->value << ' ';
    HiddenDisplay(node->child[RIGHT]);
}
Node* RedBlackTree::Successor(Node* node) {
    Node* succ = node->child[RIGHT];
    while(succ->child[LEFT] != nullptr) {
        succ = succ->child[LEFT];
    }
    return succ;
}
Node* RedBlackTree::HiddenDelete(Node* node, int value) {
    if(node == nullptr) {
        return nullptr;
    }
    if(value < node->value) {
        node->child[LEFT] = HiddenDelete(node->child[LEFT], value);
    }
    else if(value > node->value) {
        node->child[RIGHT] = HiddenDelete(node->child[RIGHT], value);
    }
    else {
        Node* tempNode = nullptr;
        if(node->child[LEFT] == nullptr || node->child[RIGHT] == nullptr) {
            tempNode = node;
        }
        else {
            tempNode = Successor(node);
        }
    }
}

void RedBlackTree::Insert(int value) {
    if(root == nullptr) {
        root = new Node(value);
        return;
    }
    Node* curr = root, * pred = nullptr;
    while(curr != nullptr) {
        pred = curr;
        if(value < curr->value) {
            curr = curr->child[LEFT];
        }
        else if(value > curr->value) {
            curr = curr->child[RIGHT];
        }
        else {
            return;
        }
    }
    Node* node = new Node(value, pred);
    pred->child[value > pred->value] = node;
    Fixup(node);
    return;
}
void RedBlackTree::Delete(int value) {
    root = HiddenDelete(root, value);
}
void RedBlackTree::Display() {
    HiddenDisplay(root);
    std::cout << std::endl;
}

}