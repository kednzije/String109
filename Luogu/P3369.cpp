#include <iostream>
#include <vector>
using namespace std;

namespace String {

class Node {
    public:
        int value, size, cnt;
        bool isRed;
        Node* parent, * child[2];
        Node();
        Node(int v);
        Node(int v, Node* p);
};
Node::Node() {
    value = size = cnt = 0;
    isRed = false;
    parent = nullptr, child[0] = child[1] = nullptr;
}
Node::Node(int v) {
    value = v, size = cnt = 1;
    isRed = false;
    parent = nullptr, child[0] = child[1] = nullptr;
}
Node::Node(int v, Node* p) {
    value = v, size = cnt = 1;
    isRed = true;
    parent = p, child[0] = child[1] = nullptr;
}

class RedBlackTree {
    private:
        const bool LEFT=0, RIGHT=1;
        Node* root;
        void Update(Node* node);
        void Rotate(Node* node, bool toRight);
        void Fixup(Node* node);
        void HiddenDisplay(Node* node);
        Node* _Successor(Node* node);
        void DeleteNode(Node* node);
        void DeleteRedNode(Node* node);
        void DeleteBlackNodeNotLeaf(Node* node);
        void DeleteBlackNodeCase1(Node* node);
        void DeleteBlackNodeCase2(Node* node);
        void DeleteBlackNodeCase3(Node* node);
        void DeleteBlackNodeCase4(Node* node);
        Node* DeleteBlackNodeCase5(Node* node);
        void DeleteBlackNodeIsLeaf(Node* node);
        int Neighbor(int value, bool toRight);
        bool Find(int value);
    public:
        RedBlackTree();
        void Insert(int value);
        void Delete(int value);
        void Display();
        int Rank(int value);
        int RankX(int rank);
        int Predecessor(int value);
        int Successor(int value);
};

RedBlackTree::RedBlackTree() {
    root = nullptr;
}
void RedBlackTree::Update(Node* node) {
    node->size = node->cnt;
    for(int i = 0; i < 2; i++) {
        if(node->child[i] != nullptr) {
            node->size += node->child[i]->size;
        }
    }
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
    Update(node);
    Update(childNode);
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
    for(int i = 1; i <= node->cnt; i++) {
        std::cout << node->value << ' ';
    }
    HiddenDisplay(node->child[RIGHT]);
}
Node* RedBlackTree::_Successor(Node* node) {
    Node* succ = node->child[RIGHT];
    while(succ->child[LEFT] != nullptr) {
        succ->size--;
        succ = succ->child[LEFT];
    }
    succ->size--;
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

bool RedBlackTree::Find(int value) {
    Node* curr = root;
    while(true) {
        if(curr == nullptr) {
            return false;
        }
        if(curr->value == value) {
            return true;
        }
        if(value < curr->value) {
            curr = curr->child[LEFT];
        }
        else {
            curr = curr->child[RIGHT];
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
        curr->size++;
        pred = curr;
        if(value < curr->value) {
            curr = curr->child[LEFT];
        }
        else if(value > curr->value) {
            curr = curr->child[RIGHT];
        }
        else {
            curr->cnt++;
            return;
        }
    }
    Node* node = new Node(value, pred);
    pred->child[value > pred->value] = node;
    Fixup(node);
    return;
}
void RedBlackTree::Delete(int value) {
    if(!Find(value)) {
        return;
    }
    Node* curr = root;
    while(true) {
        if(curr == nullptr) {
            return;
        }
        curr->size--;
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
    if(curr->cnt > 1) {
        curr->cnt--;
        return;
    }
    if(curr->child[LEFT] != nullptr && curr->child[RIGHT] != nullptr) {
        Node* succ = _Successor(curr);
        curr->value = succ->value;
        curr->cnt = succ->cnt;
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
int RedBlackTree::Rank(int value) {
    int cnt = 0;
    Node* curr = root;
    while(curr != nullptr) {
        if(value < curr->value) {
            curr = curr->child[LEFT];
        }
        else {
            if(curr->child[LEFT] != nullptr) {
                cnt += curr->child[LEFT]->size;
            }
            if(value == curr->value) {
                return cnt + 1;
            }
            cnt += curr->cnt;
            curr = curr->child[RIGHT];
        }
    }
    return cnt + 1;
}
int RedBlackTree::RankX(int rank) {
    Node* curr = root;
    int cnt = 0;
    while(curr != nullptr) {
        int leftChildSize = 0;
        if(curr->child[LEFT] != nullptr) {
            leftChildSize = curr->child[LEFT]->size;
        }
        if(leftChildSize + cnt >= rank) {
            curr = curr->child[LEFT];
        }
        else if(leftChildSize + cnt + curr->cnt < rank) {
            cnt += leftChildSize;
            cnt += curr->cnt;
            curr = curr->child[RIGHT];
        }
        else {
            return curr->value;
        }
    }
}
int RedBlackTree::Neighbor(int value, bool toRight) {
    Node* curr = root, * prev = nullptr;
    while(curr != nullptr) {
        prev = curr;
        if((curr->value > value && toRight) || (curr->value < value && !toRight)) {
            curr = curr->child[!toRight];
        }
        else {
            curr = curr->child[toRight];
        }
    }
    if((prev->value > value && toRight) || (prev->value < value && !toRight)) {
        return prev->value;
    }
    if(prev->child[toRight] == nullptr) {
        while(prev->parent != nullptr && prev == prev->parent->child[toRight]) {
            prev = prev->parent;
        }
        prev = prev->parent;
    }
    else {
        prev = prev->child[toRight];
        while(prev->child[!toRight] != nullptr) {
            prev = prev->child[!toRight];
        }
    }
    return prev->value;
}
int RedBlackTree::Predecessor(int value) {
    return Neighbor(value, LEFT);
}
int RedBlackTree::Successor(int value) {
    return Neighbor(value, RIGHT);
}
    
}

int main() {
    String::RedBlackTree t;
    int n;
    cin >> n;
    while(n--) {
        int ope, val;
        cin >> ope >> val;
        switch (ope)
        {
        case 1:
            t.Insert(val);
            break;
        case 2:
            t.Delete(val);
            break;
        case 3:
            cout << t.Rank(val) << endl;
            break;
        case 4:
            cout << t.RankX(val) << endl;
            break;
        case 5:
            cout << t.Predecessor(val) << endl;
            break;
        case 6:
            cout << t.Successor(val) << endl;
            break;
        case 7:
            t.Display();
            break;
        
        default:
            break;
        }
    }
    return  0;
}

/*
Input:
20
1 964673
5 968705
4 1
3 964673
5 965257
1 915269
1 53283
3 964673
3 53283
3 53283
1 162641
5 973984
1 948119
2 915269
2 53283
6 959161
1 531821
1 967521
2 531821
1 343410

Output:
964673
964673
1
964673
3
1
1
964673
964673

*/