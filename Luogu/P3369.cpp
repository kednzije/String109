#include <iostream>
using namespace std;

class Node {
    public:
        int value, size, cnt;
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
        void Update(Node* node);
        Node* Find(int value);
    public:
        BinarySearchTree();
        void Insert(int value);
        void Delete(int value);
        void Display();
        int FindMin();
        int FindMax();
        int Rank(int value);
        int RankX(int rank);
        int Predecessor(int value);
        int Successor(int value);
};

Node::Node() {
    value = size = cnt = 0;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v) {
    value = v, size = cnt = 1;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v, Node* p) {
    value = v, size = cnt = 1;
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
        node->leftChild->parent = node;
    }
    else if(value > node->value) {
        node->rightChild = HiddenInsert(node->rightChild, value);
        node->rightChild->parent = node;
    }
    else {
        node->cnt++;
    }
    Update(node);
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
        if(node->cnt > 1) {
            node->cnt--;
            Update(node);
            return node;
        }
        if(node->leftChild == nullptr && node->rightChild == nullptr) {
            delete node;
            return nullptr;
        }
        if(node->leftChild == nullptr) {
            Node* shouldReturn = node->rightChild;
            shouldReturn->parent = node->parent;
            delete node;
            return shouldReturn;
        }
        if(node->rightChild == nullptr) {
            Node* shouldReturn = node->leftChild;
            shouldReturn->parent = node->parent;
            delete node;
            return shouldReturn;
        }
        Node* succNode = HiddenFindMin(node->rightChild);
        node->value = succNode->value;
        node->rightChild = HiddenDelete(node->rightChild, succNode->value);
        Update(node);
        return node;
    }
    if(value < node->value) {
        node->leftChild = HiddenDelete(node->leftChild, value);
    }
    else {
        node->rightChild = HiddenDelete(node->rightChild, value);
    }
    Update(node);
    return node;
}
void BinarySearchTree::HiddenDisplay(Node* node) {
    if(node->leftChild != nullptr) {
        HiddenDisplay(node->leftChild);
    }
    for(int i = 1; i <= node->size; i++) {
        std::cout << node->value << ' ';
    }
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
void BinarySearchTree::Update(Node* node) {
    node->size = node->cnt;
    if(node->leftChild != nullptr) {
        node->size += node->leftChild->size;
        node->leftChild->parent = node;
    }
    if(node->rightChild != nullptr) {
        node->size += node->rightChild->size;
        node->rightChild->parent = node;
    }
}
int BinarySearchTree::Rank(int value) {
    int cnt = 0;
    Node* curr = root;
    while(curr != nullptr) {
        if(value == curr->value) {
            if(curr->leftChild != nullptr) {
                cnt += curr->leftChild->size;
            }
            return cnt + 1;
        }
        else if(value < curr->value) {
            curr = curr->leftChild;
        }
        else {
            if(curr->leftChild != nullptr) {
                cnt += curr->leftChild->size;
            }
            cnt += curr->cnt;
            curr = curr->rightChild;
        }
    }
}
int BinarySearchTree::RankX(int rank) {
    Node* curr = root;
    int cnt = 0;
    while(curr != nullptr) {
        if(curr->leftChild != nullptr) {
            if(curr->leftChild->size + cnt >= rank) {
                curr = curr->leftChild;
            }
            else {
                if(curr->leftChild->size + cnt + 1 >= rank 
                    && curr->leftChild->size + cnt + curr->cnt <= rank) {
                    return curr->value;
                }
                else {
                    if(curr->leftChild != nullptr) {
                        cnt += curr->leftChild->size;
                    }
                    cnt += curr->cnt;
                    curr = curr->rightChild;
                }
            }
        }
        else {
            if(cnt + 1 >= rank && cnt + curr->cnt <= rank) {
                return curr->value;
            }
            else {
                cnt += curr->cnt;
                curr = curr->rightChild;
            }
        }
    }
}
Node* BinarySearchTree::Find(int value) {
    Node* curr = root;
    while(curr != nullptr) {
        if(curr->value == value) {
            return curr;
        }
        if(value < curr->value) {
            curr = curr->leftChild;
        }
        else {
            curr = curr->rightChild;
        }
    }
}
int BinarySearchTree::Predecessor(int value) {
    Node* curr = root, * prev = nullptr;
    while(curr != nullptr) {
        prev = curr;
        if(curr->value < value) {
            curr = curr->rightChild;
        }
        else {
            curr = curr->leftChild;
        }
    }
    if(prev->value < value) {
        return prev->value;
    }
    if(prev->leftChild == nullptr) {
        while(prev->parent != nullptr && prev == prev->parent->leftChild) {
            prev = prev->parent;
        }
        return prev->parent->value;
    }
    else {
        prev = prev->leftChild;
        while(prev->rightChild != nullptr) {
            prev = prev->rightChild;
        }
        return prev->value;
    }
}
int BinarySearchTree::Successor(int value) {
    Node* curr = root, * prev = nullptr;
    while(curr != nullptr) {
        prev = curr;
        if(curr->value > value) {
            curr = curr->leftChild;
        }
        else {
            curr = curr->rightChild;
        }
    }
    if(prev->value > value) {
        return prev->value;
    }
    if(prev->rightChild == nullptr) {
        while(prev->parent != nullptr && prev == prev->parent->rightChild) {
            prev = prev->parent;
        }
        return prev->parent->value;
    }
    else {
        prev = prev->rightChild;
        while(prev->leftChild != nullptr) {
            prev = prev->leftChild;
        }
        return prev->value;
    }
}

int main() {
    BinarySearchTree bst;
    int n;
    cin >> n;
    while(n--) {
        int ope, val;
        cin >> ope >> val;
        switch (ope)
        {
        case 1:
            bst.Insert(val);
            break;
        case 2:
            bst.Delete(val);
            break;
        case 3:
            cout << bst.Rank(val) << endl;
            break;
        case 4:
            cout << bst.RankX(val) << endl;
            break;
        case 5:
            cout << bst.Predecessor(val) << endl;
            break;
        case 6:
            cout << bst.Successor(val) << endl;
            break;
        
        default:
            break;
        }
    }
    return  0;
}