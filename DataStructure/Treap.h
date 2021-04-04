#include <time.h>
#include <stdlib.h>

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
        void Split(Node<T> * node, T value, Node<T> *(* p1), Node<T> *(* p2));
        Node<T> * Merge(Node<T> * u, Node<T> * v);
        Node<T> * Find(Node<T> * node, T value);
        void Update(Node<T> * node);
        void HiddenDisplay(Node<T> * node);
    public:
        Treap();
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
template <class T> void Treap<T>::Split(Node<T> * node, T value, Node<T> *(* p1), Node<T> *(* p2)) {
    if(node == nullptr) {
        (*p1) = (*p2) = nullptr;
        return;
    }
    if(value < node->value) {
        (*p2) = node;
        Split(node->leftChild, value, p1, &((*p2)->leftChild));
    }
    else {
        (*p1) = node;
        Split(node->rightChild, value, &((*p1)->rightChild), p2);
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
template <class T> void Treap<T>::Insert(T value) {
    Node<T> * p1, * p2;
    Split(root, value, &p1, &p2);
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
    Node<int> * p1, * p2, * p3, * shouldDelete;
    Split(root, value - 1, &p1, &p2);
    Split(p2, value, &p2, &p3);
    delete p2;
    root = Merge(p1, p3);
    return;
}
template <class T> int Treap<T>::Rank(T value) {
    return 0;
}
template <> int Treap<int>::Rank(int value) {
    Node<int> * p1, * p2;
    Split(root, value - 1, &p1, &p2);
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
    Split(root, value - 1, &p1, &p2);
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
    Split(root, value, &p1, &p2);
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
        using Treap<T>::Split;
        using Treap<T>::Merge;
    public:
        void Insert(T value);
        void Erase(T value);
};
template <class T> void TreapMultiset<T>::Insert(T value) {
    Node<T> * p1, * p2;
    Split(root, value, &p1, &p2);
    p1 = Merge(p1, new Node<T>(value));
    root = Merge(p1, p2);
}
template <class T> void TreapMultiset<T>::Erase(T value) {
    return;
}
template <> void TreapMultiset<int>::Erase(int value) {
    Node<int> * p1, * p2, * p3;
    Split(root, value - 1, &p1, &p2);
    Split(p2, value, &p2, &p3);
    if(p2 != nullptr) {
        p1 = Merge(p1, Merge(p2->leftChild, p2->rightChild));
    }
    delete p2;
    root = Merge(p1, p3);
    return;
}

}