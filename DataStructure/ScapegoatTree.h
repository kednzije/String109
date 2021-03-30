#include <vector>
#include <iostream>

namespace String {

class Node {
    public:
        int value, size;
        bool deleted;
        Node* leftChild, * rightChild;
        Node();
        Node(int v);
};
Node::Node() {
    value = size = 0;
    deleted = false;
    leftChild = rightChild = nullptr;
}
Node::Node(int v) {
    value = v, size = 1;
    deleted = false;
    leftChild = rightChild = nullptr;
}

class ScapegoatTree {
    private:
        const double ALPHA = 0.75;
        Node* root;
        int deletedCnt;
        void Update(Node* node);
        bool ShouldRes(Node* node);
        Node* BuildFromVec(std::vector<int> &vec, int l, int r);
        void InorderTraversal(Node* node, std::vector<int> &vec);
        Node* Restructure(Node* node);
        Node* HiddenInsert(Node* node, int value);
        Node* Check(Node* node, int value);
        void Mark(Node* node, int value);
        void HiddenDisplay(Node* node);
    public:
        ScapegoatTree();
        void Insert(int value);
        void Delete(int value);
        void Display();
};

ScapegoatTree::ScapegoatTree() {
    root = nullptr;
    deletedCnt = 0;
}
void ScapegoatTree::Update(Node* node) {
    node->size = 1;
    if(node->leftChild != nullptr) {
        node->size += node->leftChild->size;
    }
    if(node->rightChild != nullptr) {
        node->size += node->rightChild->size;
    }
}
bool ScapegoatTree::ShouldRes(Node* node) {
    int biggerSize = -1;
    if(node->leftChild != nullptr && node->leftChild->size > biggerSize) {
        biggerSize = node->leftChild->size;
    }
    if(node->rightChild != nullptr && node->rightChild->size > biggerSize) {
        biggerSize = node->rightChild->size;
    }
    return 1.0 * biggerSize > ALPHA * node->size;
}
Node* ScapegoatTree::BuildFromVec(std::vector<int> &vec, int l, int r) {
    if(l > r) {
        return nullptr;
    }
    Node* node = new Node(vec[(l + r) / 2]);
    node->leftChild = BuildFromVec(vec, l, (l + r) / 2 - 1);
    node->rightChild = BuildFromVec(vec, (l + r) / 2 + 1, r);

    Update(node);
    return node;
}
void ScapegoatTree::InorderTraversal(Node* node, std::vector<int> &vec) {
    if(node == nullptr) {
        return;
    }
    InorderTraversal(node->leftChild, vec);
    if(!node->deleted) {
        vec.push_back(node->value);
    }
    InorderTraversal(node->rightChild, vec);

    delete node;
    return;
}
Node* ScapegoatTree::Restructure(Node* node) {
    std::vector<int> vec;
    InorderTraversal(node, vec);
    return BuildFromVec(vec, 0, vec.size() - 1);
}
Node* ScapegoatTree::HiddenInsert(Node* node, int value) {
    if(node == nullptr) {
        return new Node(value);
    }
    if(value < node->value) {
        node->leftChild = HiddenInsert(node->leftChild, value);
    }
    else if(value > node->value) {
        node->rightChild = HiddenInsert(node->rightChild, value);
    }
    else {
        node->deleted = false;
    }

    Update(node);
    return node;
}
Node* ScapegoatTree::Check(Node* node, int value) {
    if(node == nullptr) {
        return nullptr;
    }
    if(ShouldRes(node)) {
        return Restructure(node);
    }
    if(value < node->value) {
        node->leftChild = Check(node->leftChild, value);
    }
    else if(value > node->value) {
        node->rightChild = Check(node->rightChild, value);
    }

    Update(node);
    return node;
}
void ScapegoatTree::Mark(Node* node, int value) {
    if(node == nullptr) {
        return;
    }
    if(value == node->value) {
        node->deleted = true;
        return;
    }
    if(value < node->value) {
        Mark(node->leftChild, value);
    }
    else {
        Mark(node->rightChild, value);
    }
    return;
}
void ScapegoatTree::HiddenDisplay(Node* node) {
    if(node == nullptr) {
        return;
    }
    HiddenDisplay(node->leftChild);
    if(!node->deleted) {
        std::cout << node->value << ' ';
    }
    HiddenDisplay(node->rightChild);
    return;
}

void ScapegoatTree::Insert(int value) {
    root = HiddenInsert(root, value);
    root = Check(root, value);
}
void ScapegoatTree::Delete(int value) {
    deletedCnt++;
    Mark(root, value);
    if(deletedCnt > root->size / 2) {
        root = Restructure(root);
        deletedCnt = 0;
    }
}
void ScapegoatTree::Display() {
    HiddenDisplay(root);
    std::cout << std::endl;
    return;
}

}