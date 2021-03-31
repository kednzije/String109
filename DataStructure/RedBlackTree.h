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
        void DeleteNode(Node* node);
        void DeleteRedNode(Node* node);
        void DeleteBlackNodeNotLeaf(Node* node);
        void DeleteBlackNodeCase1(Node* node);
        void DeleteBlackNodeCase2(Node* node);
        void DeleteBlackNodeCase3(Node* node);
        void DeleteBlackNodeCase4(Node* node);
        Node* DeleteBlackNodeCase5(Node* node);
        void DeleteBlackNodeIsLeaf(Node* node);
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
/*void RedBlackTree::Rotate(Node* node, bool toRight) {
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
}*/
void RedBlackTree::Rotate(Node* node, bool toRight) {
    Node* p = node->parent;
    Node* childNode = node->child[!toRight];

    if(childNode->child[toRight] != nullptr) {
        childNode->child[toRight]->parent = node; 
    }
    node->child[!toRight] = childNode->child[toRight];

    childNode->child[toRight] = node;
    node->parent = childNode;

    childNode->parent = p;
    if(p == nullptr) {
        root = childNode;
    }
    else {
        p->child[node == p->child[RIGHT]] = childNode;
    }
    return;
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
void RedBlackTree::DeleteNode(Node* node) {
    Node* p = node->parent;
    if(p == nullptr) {
        root = nullptr;
        delete node;
        return;
    }
    p->child[node == p->child[RIGHT]] = nullptr;
    delete node;
    return;
} 
void RedBlackTree::DeleteRedNode(Node* node) {
    DeleteNode(node);
}
void RedBlackTree::DeleteBlackNodeNotLeaf(Node* node) {
    Node* childNode;
    if(node->child[LEFT] == nullptr) {
        childNode = node->child[RIGHT];
    }
    else {
        childNode = node->child[LEFT];
    }

    childNode->isRed = false;
    Node* p = node->parent;
    childNode->parent = p;
    if(p == nullptr) {
        root = childNode;
    }
    else {
        p->child[node == p->child[RIGHT]] = childNode;
    }
    delete node;
}
void RedBlackTree::DeleteBlackNodeCase1(Node* node) {
    // Case 1: The brother of the node to be deleted is red.
    //         This function is used to turn this case to followed cases.
    Node* p = node->parent;
    bool isLeftChild = (node == p->child[LEFT]);

    Node* bro = p->child[isLeftChild];
    p->isRed = true;
    bro->isRed = false;
    Rotate(p, !isLeftChild);
}
void RedBlackTree::DeleteBlackNodeCase2(Node* node) {
    // Case 2: The brother of the node to be deleted is black
    //         and the further nephew is red.
    Node* p = node->parent;
    bool isLeftChild = (node == p->child[LEFT]);

    Node* bro = p->child[isLeftChild];
    bool tempColor = p->isRed;
    p->isRed = bro->isRed;
    bro->isRed = tempColor;

    bro->child[isLeftChild]->isRed = false;
    Rotate(p, !isLeftChild);
}
void RedBlackTree::DeleteBlackNodeCase3(Node* node) {
    // Case 3: The brother of the node to be deleted is black
    //         and the closer nephew is red.
    //         This function is used to turn this case to case 2.
    Node* p = node->parent;
    bool isLeftChild = (node == p->child[LEFT]);

    Node* bro = p->child[isLeftChild];
    
    bro->isRed = true;
    bro->child[!isLeftChild]->isRed = false;

    Rotate(bro, isLeftChild);
}
void RedBlackTree::DeleteBlackNodeCase4(Node* node) {
    // Case 4: The brother of the node to be deleted is black
    //         and both the nephews are black (and are both nullptr)
    //         when the parent of the node is red.
    Node* p = node->parent;
    bool isLeftChild = (node == p->child[LEFT]);

    Node* bro = p->child[isLeftChild];

    p->isRed = false;
    bro->isRed = true;
}
Node* RedBlackTree::DeleteBlackNodeCase5(Node* node) {
    // Case 5: The brother of the node to be deleted is black
    //         and both the nephews are black (and are both nullptr)
    //         when the parent of the node is black.
    Node* p = node->parent;
    bool isLeftChild = (node == p->child[LEFT]);

    Node* bro = p->child[isLeftChild];
    bro->isRed = true;
    return p;
}
void RedBlackTree::DeleteBlackNodeIsLeaf(Node* node) {
    Node* curr = node;
    while(curr != root) {
        Node* p = curr->parent;
        bool isLeftChild = (curr == p->child[LEFT]);
        Node* bro = p->child[isLeftChild];
        if(bro->isRed) {
            DeleteBlackNodeCase1(curr);
            continue;
        }
        Node* furtherNephew = bro->child[isLeftChild];
        Node* closerNephew = bro->child[!isLeftChild];
        if(furtherNephew != nullptr && furtherNephew->isRed) {
            DeleteBlackNodeCase2(curr);
            break;
        }
        if(closerNephew != nullptr && closerNephew->isRed) {
            DeleteBlackNodeCase3(curr);
            continue;
        }
        if(p->isRed) {
            DeleteBlackNodeCase4(curr);
            break;
        }

        curr = DeleteBlackNodeCase5(curr);
    }
    DeleteNode(node);
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
    Node* curr = root;
    while(true) {
        if(curr == nullptr) {
            return;
        }
        if(curr->value == value) {
            break;
        }
        if(value < curr->value) {
            curr = curr->child[LEFT];
        }
        else {
            curr = curr->child[RIGHT];
        }
    }
    if(curr->child[LEFT] != nullptr && curr->child[RIGHT] != nullptr) {
        Node* succ = Successor(curr);
        curr->value = succ->value;
        curr = succ;
    }
    if(curr->child[LEFT] == nullptr && curr->child[RIGHT] == nullptr) {
        if(curr->isRed) {
            DeleteRedNode(curr);
        }
        else {
            DeleteBlackNodeIsLeaf(curr);
        }
    }
    else {
        DeleteBlackNodeNotLeaf(curr);
    }
}
void RedBlackTree::Display() {
    HiddenDisplay(root);
    std::cout << std::endl;
}

}