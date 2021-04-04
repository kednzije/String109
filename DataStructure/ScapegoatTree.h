#include <vector>
#include <iostream>

namespace String {

class Node {
    public:
        int value, size, cnt;
        Node* leftChild, * rightChild, * parent;
        Node();
        Node(int v);
        Node(int v, int c);
};
Node::Node() {
    value = size = cnt = 0;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v) {
    value = v, size = cnt = 1;
    leftChild = rightChild = parent = nullptr;
}
Node::Node(int v, int c) {
    value = v, size = cnt = c;
    leftChild = rightChild = parent = nullptr;
}

class ScapegoatTree {
    private:
        const double ALPHA = 0.75;
        Node* root;
        int deletedCnt;
        void Update(Node* node);
        bool ShouldRes(Node* node);
        Node* BuildFromVec(std::vector<std::pair <int, int> > &vec, int l, int r);
        void InorderTraversal(Node* node, std::vector<std::pair <int, int> > &vec);
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
        int Rank(int value);
        int RankX(int rank);
        int Predecessor(int value);
        int Successor(int value);
};

ScapegoatTree::ScapegoatTree() {
    root = nullptr;
    deletedCnt = 0;
}
void ScapegoatTree::Update(Node* node) {
    node->cnt = (node->cnt < 0 ? 0 : node->cnt);
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
Node* ScapegoatTree::BuildFromVec(std::vector<std::pair <int, int> > &vec, int l, int r) {
    if(l > r) {
        return nullptr;
    }
    Node* node = new Node(vec[(l + r) / 2].first, vec[(l + r) / 2].second);
    node->leftChild = BuildFromVec(vec, l, (l + r) / 2 - 1);
    node->rightChild = BuildFromVec(vec, (l + r) / 2 + 1, r);

    Update(node);
    return node;
}
void ScapegoatTree::InorderTraversal(Node* node, std::vector<std::pair<int, int> > &vec) {
    if(node == nullptr) {
        return;
    }
    InorderTraversal(node->leftChild, vec);
    if(node->cnt > 0) {
        vec.push_back(std::make_pair(node->value, node->cnt));
    }
    InorderTraversal(node->rightChild, vec);

    delete node;
    return;
}
Node* ScapegoatTree::Restructure(Node* node) {
    std::vector<std::pair <int, int> > vec;
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
        node->cnt++;
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
        if(node->cnt > 0) {
            node->size--;
            node->cnt--;
        }
        return;
    }
    if(value < node->value) {
        Mark(node->leftChild, value);
    }
    else {
        Mark(node->rightChild, value);
    }
    Update(node);
    return;
}
void ScapegoatTree::HiddenDisplay(Node* node) {
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
int ScapegoatTree::Rank(int value) {
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
                return cnt + 1;
            }
            cnt += curr->cnt;
            curr = curr->rightChild;
        }
    }
    return cnt + 1;
}
int ScapegoatTree::RankX(int rank) {
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
int ScapegoatTree::Predecessor(int value) {
    return RankX(Rank(value) - 1);
}
int ScapegoatTree::Successor(int value) {
    return RankX(Rank(value + 1));
}

}