
#include <iostream>
#include <vector>
using namespace std;

namespace String {

class Node {
    public:
        int value, cnt, size;
        Node* leftChild, * rightChild, * parent;
        Node();
        Node(int v);
        Node(int v, Node* p);
};
Node::Node() {
    value = cnt = size = 0;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v) {
    value = v, cnt = size = 1;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v, Node* p) {
    value = v, cnt = size = 1;
    leftChild = rightChild = nullptr, parent = p;
}

class SplayTree {
    private:
        Node* root;
        int tot;
        void MaintainSize(Node* node);
        bool isLeftChild(Node* node);
        void Delete(Node* node);
        void ReplaceSon(Node* p, Node* child, Node* newChild);
        void Rotate(Node* node);
        void Splay(Node* node);
        Node* Merge(Node* l, Node* r);
        void HiddenDisplay(Node* node);
    public:
        SplayTree();
        void Display();
        void Insert(int value);
        int Rank(int value);
        void Delete(int value);
        int RankX(int rank);
        int Predecessor(int value);
        int Successor(int value);
};
SplayTree::SplayTree() {
    root = nullptr;
    tot = 0;
}
void SplayTree::MaintainSize(Node* node) {
    if(node == nullptr) {
        return;
    }
    node->size = node->cnt;
    if(node->leftChild != nullptr) {
        node->size += node->leftChild->size;
    }
    if(node->rightChild != nullptr) {
        node->size += node->rightChild->size;
    }
    return;
}
bool SplayTree::isLeftChild(Node* node) {
    return node == node->parent->leftChild;
}
void SplayTree::Delete(Node* node) {
    delete node;
}
void SplayTree::ReplaceSon(Node* p, Node* child, Node* newChild) {
    if(p != nullptr) {
        if(p->leftChild == child) {
            p->leftChild = newChild;
        }
        if(p->rightChild == child) {
            p->rightChild = newChild;
        }
    }
    newChild->parent = p;
}
void SplayTree::Rotate(Node* node) {
    Node* p = node->parent;
    if(p != nullptr) {
        Node* g = p->parent;
        if(isLeftChild(node)) {
            ReplaceSon(g, p, node);
            p->leftChild = node->rightChild;
            node->rightChild = p;

            if(p->leftChild != nullptr) {
                p->leftChild->parent = p;
            }
            p->parent = node;
        }
        else {
            ReplaceSon(g, p, node);
            p->rightChild = node->leftChild;
            node->leftChild = p;

            if(p->rightChild != nullptr) {
                p->rightChild->parent = p;
            }
            p->parent = node;
        }

        MaintainSize(p);
        MaintainSize(node);
    }
}
void SplayTree::Splay(Node* node) {
    while(node->parent != nullptr) {
        if(node->parent->parent != nullptr) {
            if(isLeftChild(node) == isLeftChild(node->parent)) {
                Rotate(node->parent);
            }
            else {
                Rotate(node);
            }
        }
        Rotate(node);
    }
    root = node;
}
Node* SplayTree::Merge(Node* l, Node* r) {
    if(l == nullptr) {
        return r;
    }
    if(r == nullptr) {
        return l;
    }
    Node* cur = l;
    while(cur->rightChild != nullptr) {
        cur = cur->rightChild;
    }
    Splay(cur);
    cur->rightChild = r;
    r->parent = cur;
    MaintainSize(cur);
}

void SplayTree::Insert(int value) {
    tot++;
    if(root == nullptr) {
        root = new Node(value);
        return;
    }
    Node* cur = root;
    while(true) {
        cur->size++;

        if(cur->value == value) {
            cur->cnt++;
            Splay(cur);
            break;
        }

        if(value < cur->value) {
            if(cur->leftChild == nullptr) {
                cur->leftChild = new Node(value, cur);
                Splay(cur->leftChild);
                break;
            }

            cur = cur->leftChild;
        }
        else {
            if(cur->rightChild == nullptr) {
                cur->rightChild = new Node(value, cur);
                Splay(cur->rightChild);
                break;
            }

            cur = cur->rightChild;
        }
    }
}
int SplayTree::Rank(int value) {
    int cnt = 0;
    Node* curr = root;
    while(curr != nullptr) {
        if(value < curr->value) {
            curr = curr->leftChild;
        }
        else {
            if(curr->leftChild != nullptr) {
                cnt += curr->leftChild->size;
            }
            if(value == curr->value) {
                Splay(curr);
                return cnt + 1;
            }
            cnt += curr->cnt;
            curr = curr->rightChild;
        }
    }
    return cnt + 1;
}
void SplayTree::Delete(int value) {
    Rank(value);
    if(root->cnt > 1) {
        root->cnt--;
        return;
    }
    Node* l = root->leftChild, * r = root->rightChild;
    if(l != nullptr) {
        l->parent = nullptr;
    }
    if(r != nullptr) {
        r->parent = nullptr;
    }
    Node* shouldDelete = root;
    root = Merge(l, r);
    delete shouldDelete;
}
int SplayTree::RankX(int rank) {
    Node* curr = root;
    int cnt = 0;
    while(curr != nullptr) {
        int leftChildSize = 0;
        if(curr->leftChild != nullptr) {
            leftChildSize = curr->leftChild->size;
        }
        if(leftChildSize + cnt >= rank) {
            curr = curr->leftChild;
        }
        else if(leftChildSize + cnt + curr->cnt < rank) {
            cnt += leftChildSize;
            cnt += curr->cnt;
            curr = curr->rightChild;
        }
        else {
            return curr->value;
        }
    }
}
int SplayTree::Predecessor(int value) {
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
        prev = prev->parent;
    }
    else {
        prev = prev->leftChild;
        while(prev->rightChild != nullptr) {
            prev = prev->rightChild;
        }
    }
    return prev->value;
}
int SplayTree::Successor(int value) {
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
        prev = prev->parent;
    }
    else {
        prev = prev->rightChild;
        while(prev->leftChild != nullptr) {
            prev = prev->leftChild;
        }
    }
    return prev->value;
}
void SplayTree::HiddenDisplay(Node* node) {
    if(node == nullptr) {
        return;
    }
    HiddenDisplay(node->leftChild);
    for(int i = 1; i <= node->cnt; i++) {
        std::cout << node->value << ' ';
    }
    HiddenDisplay(node->rightChild);
    return;
}
void SplayTree::Display() {
    HiddenDisplay(root);
    std::cout << std::endl;
    return;
}

}

int main() {
    freopen("Data.in", "r", stdin);
    freopen("AcceptedRes.out", "w", stdout);
    String::SplayTree t;
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