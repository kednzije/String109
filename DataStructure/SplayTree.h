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
    public:
        SplayTree();
        void Insert(int value);
        int Rank(int value);
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
            newChild->parent = p;
        }
        if(p->rightChild == child) {
            p->rightChild = newChild;
            newChild->parent = p;
        }
    }
}
void SplayTree::Rotate(Node* node) {
    Node* p = node->parent;
    if(p != nullptr) {
        Node* g = p->parent;
        if(isLeftChild(node)) {
            ReplaceSon(g, p, node);
            p->leftChild = node->rightChild;
            node->rightChild = p;

            p->leftChild->parent = p;
            p->parent = node;
        }
        else {
            ReplaceSon(g, p, node);
            p->rightChild = node->leftChild;
            node->leftChild = p;

            p->rightChild->parent = p;
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
    Node* cur = root;
    int rank = 0;
    while(true) {
        if(cur == nullptr) {
            return -1;
        }

        if(cur->value == value) {
            Splay(cur);
            return rank + 1;
        }
        if(value < cur->value) {
            cur = cur->leftChild;
        }
        else {
            if(cur->leftChild != nullptr) {
                rank += cur->leftChild->size + cur->cnt;
            }
            cur = cur->rightChild;
        }
    }
}

};