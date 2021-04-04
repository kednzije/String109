#include <iostream>
#include <vector>
using namespace std;

namespace String {

template <class T> class Node {
    public:
        T value;
        int cnt, size;
        int priority;
        Node* leftChild, * rightChild, * parent;
        Node();
        Node(T v);
        Node(T v, Node* p);
};

template <class T> Node<T>::Node() {
    cnt = size = 0;
    priority = 0;
    leftChild = rightChild = parent = nullptr;
}
template <class T> Node<T>::Node(T v) {
    cnt = size = 1;
    priority = rand();
    value = v;
    leftChild = rightChild = parent = nullptr;
}
template <class T> Node<T>::Node(T v, Node* p) {
    cnt = size = 1;
    priority = rand();
    value = v;
    leftChild = rightChild = nullptr;
    parent = p;
}

template <class T> class Treap {
    protected:
        Node<T> * root;
        void Split_v(Node<T> * node, T value, Node<T> *(* p1), Node<T> *(* p2));
        void Split_k(Node<T> * node, int rank, Node<T> *(* p1), Node<T> *(* p2));
        Node<T> * Merge(Node<T> * u, Node<T> * v);
        Node<T> * Find(Node<T> * node, T value);
        void Update(Node<T> * node);
        void HiddenDisplay(Node<T> * node);
    public:
        Treap();
        int Count(T value);
        void Insert(T value);
        void Erase(T value);
        int Rank(T value);
        int RankX(int rank);
        T Predecessor(T value);
        T Successor(T value);
        void Display();
};

template <class T> Treap<T>::Treap() {
    root = nullptr;
}
template <class T> void Treap<T>::Update(Node<T> * node) {
    if(node == nullptr) {
        return;
    }
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
template <class T> void Treap<T>::Split_v(Node<T> * node, T value, Node<T> *(* p1), Node<T> *(* p2)) {
    if(node == nullptr) {
        // return std::make_pair(nullptr, nullptr);
        (*p1) = (*p2) = nullptr;
        return;
    }
    if(value < node->value) {
        // std::pair <Node<T> * , Node<T> * > childSplit = Split(node->leftChild, value);
        // node->leftChild = childSplit.second;
        // if(childSplit.second != nullptr) {
        //     childSplit.second->parent = node->leftChild;
        // }
        // return std::make_pair(childSplit.first, node);
        (*p2) = node;
        Split_v(node->leftChild, value, p1, &((*p2)->leftChild));
    }
    else {
        // std::pair <Node<T> * , Node<T> * > childSplit = Split(node->rightChild, value);
        // node->rightChild = childSplit.first;
        // if(childSplit.first != nullptr) {
        //     childSplit.first->parent = node->rightChild;
        // }
        // return std::make_pair(node, childSplit.second);
        (*p1) = node;
        Split_v(node->rightChild, value, &((*p1)->rightChild), p2);
    }
    Update(node);
}
template <class T> void Treap<T>::Split_k(Node<T> * node, int rank, Node<T> *(* p1), Node<T> *(* p2)) {
    if(node == nullptr) {
        (*p1) = (*p2) = nullptr;
        return;
    }
    int leftChildSize = 0;
    if(node->leftChild != nullptr) {
        leftChildSize = node->leftChild->size;
    }
    if(rank <= leftChildSize) {
        (*p2) = node;
        Split_k(node->leftChild, rank, p1, &(*p2)->leftChild);
    }
    else {
        (*p1) = node;
        Split_k(node->rightChild, rank - leftChildSize - 1, &((*p1)->rightChild), p2);
    }
    Update(node);
} 
template <class T> Node<T> * Treap<T>::Merge(Node<T> * u, Node<T> * v) {
    if(u == nullptr) {
        Update(v);
        return v;
    }
    if(v == nullptr) {
        Update(u);
        return u;
    }
    if(u->priority > v->priority) {
        u->rightChild = Merge(u->rightChild, v);
        Update(u);
        return u;
    }
    else {
        v->leftChild = Merge(u, v->leftChild);
        Update(v);
        return v;
    }
}
template <class T> Node<T> * Treap<T>::Find(Node<T> * node, T value) {
    if(node == nullptr) {
        return nullptr;
    }
    if(value < node->value) {
        return Find(node->leftChild, value);
    }
    else if(value > node->value) {
        return Find(node->rightChild, value);
    }

    return node;
}
template <class T> int Treap<T>::Count(T value) {
    Node<T> * node = Find(root, value);
    if(node != nullptr) {
        return node->cnt;
    }
    else {
        return 0;
    }
}
template <class T> void Treap<T>::Insert(T value) {
    Node<T> * p1, * p2;
    Split_v(root, value, &p1, &p2);
    Node<T> * node = Find(p1, value);
    if(node == nullptr) {
        p1 = Merge(p1, new Node<T>(value));
    }
    root = Merge(p1, p2);
}
template <class T> void Treap<T>::Erase(T value) {
    return;
}
template <>  void Treap<int>::Erase(int value) {
    Node<int> * p1, * p2, * p3;
    Split_v(root, value, &p1, &p2);
    Split_v(p2, value, &p2, &p3);
    delete p2;
    root = Merge(p1, p3);
    return;
}
template <class T> int Treap<T>::Rank(T value) {
    return 0;
}
template <> int Treap<int>::Rank(int value) {
    Node<int> * p1, * p2;
    Split_v(root, value - 1, &p1, &p2);
    int rank = 1;
    if(p1 != nullptr) {
        rank += p1->size;
    }
    root = Merge(p1, p2);
    return rank;
}
template <class T> int Treap<T>::RankX(int rank) {
    Node<T>* curr = root;
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
template <class T> T Treap<T>::Predecessor(T value) {
    return value;
}
template <> int Treap<int>::Predecessor(int value) {
    Node<int> * p1, * p2;
    Split_v(root, value - 1, &p1, &p2);
    Node<int> * curr = p1;
    if(curr == nullptr) {
        root = Merge(p1, p2);
        return value;
    }
    while(curr->rightChild != nullptr) {
        curr = curr->rightChild;
    }
    root = Merge(p1, p2);
    return curr->value;
}
template <class T> T Treap<T>::Successor(T value) {
    return value;
}
template <> int Treap<int>::Successor(int value) {
    Node<int> * p1, * p2;
    Split_v(root, value, &p1, &p2);
    Node<int> * curr = p2;
    if(curr == nullptr) {
        root = Merge(p1, p2);
        return value;
    }
    while(curr->leftChild != nullptr) {
        curr = curr->leftChild;
    }
    root = Merge(p1, p2);
    return curr->value;
}
template <class T> void Treap<T>::HiddenDisplay(Node<T> * node) {
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
template <class T> void Treap<T>::Display() {
    HiddenDisplay(root);
    std::cout << std::endl;
    return;
}

template <class T> class TreapSet: public Treap<T> {};
template <class T> class TreapMultiset: public Treap<T> {
    protected:
        using Treap<T>::root;
        using Treap<T>::Find;
        using Treap<T>::Split_v;
        using Treap<T>::Merge;
    public:
        void Insert(T value);
        void Erase(T value);
};
template <class T> void TreapMultiset<T>::Insert(T value) {
    Node<T> * p1, * p2;
    Split_v(root, value, &p1, &p2);
    Node<T> * node = Find(p1, value);
    if(node == nullptr) {
        p1 = Merge(p1, new Node<T>(value));
    }
    else {
        node->cnt++;
    }
    root = Merge(p1, p2);
}
template <class T> void TreapMultiset<T>::Erase(T value) {
    return;
}
template <> void TreapMultiset<int>::Erase(int value) {
    Node<int> * p1, * p2, * p3;
    Split_v(root, value - 1, &p1, &p2);
    Split_v(p2, value, &p2, &p3);
    if(p2 == nullptr) {}
    else if(p2->cnt > 1) {
        p2->cnt--;
        p1 = Merge(p1, p2);
    }
    else {
        delete p2;
    }
    root = Merge(p1, p3);
    return;
}

}

int main() {
    freopen("Data.in", "r", stdin);
    freopen("WrongRes.out", "w", stdout);
    String::TreapMultiset<int> t;
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
            t.Erase(val);
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
        // case 7:
        //     t.Display();
        //     break;
        
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