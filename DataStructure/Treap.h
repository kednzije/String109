#include <utility>
#include <time.h>
#include <stdlib.h>

namespace String {

template <class T> class Node {
    public:
        T value;
        int priority;
        Node* leftChild, * rightChild, * parent;
        Node();
        Node(T v);
        Node(T v, Node* p);
};

template <class T> Node<T>::Node() {
    priority = 0;
    leftChild = rightChild = parent = nullptr;
}
template <class T> Node<T>::Node(T v) {
    priority = rand();
    value = v;
    leftChild = rightChild = parent = nullptr;
}
template <class T> Node<T>::Node(T v, Node* p) {
    priority = rand();
    value = v;
    leftChild = rightChild = nullptr;
    parent = p;
}

template <class T> class Treap {
    protected:
        Node<T> * root;
        std::pair <Node<T> * , Node<T> * > Split(Node<T> * node, T value);
        Node<T> * Merge(Node<T> * u, Node<T> * v);
        Node<T> * Find(Node<T> * node, T value);
    public:
        Treap();
        int Count(T value);
        void Insert(T value);
        void Erase(T value);
};

template <class T> Treap<T>::Treap() {
    root = nullptr;
}
template <class T> std::pair <Node<T> * , Node<T> * > Treap<T>::Split(Node<T> * node, T value) {
    if(node == nullptr) {
        return std::make_pair(nullptr, nullptr);
    }
    if(value < node->value) {
        std::pair <Node<T> * , Node<T> * > childSplit = Split(node->leftChild, value);
        node->leftChild = childSplit.second;
        return std::make_pair(childSplit.first, node);
    }
    else {
        std::pair <Node<T> * , Node<T> * > childSplit = Split(node->rightChild, value);
        node->rightChild = childSplit.first;
        return std::make_pair(node, childSplit.second);
    }
}
template <class T> Node<T> * Treap<T>::Merge(Node<T> * u, Node<T> * v) {
    if(u == nullptr) {
        return v;
    }
    if(v == nullptr) {
        return u;
    }
    if(u->priority > v->priority) {
        u->rightChild = Merge(u->rightChild, v);
        return u;
    }
    else {
        v->leftChild = Merge(u, v->leftChild);
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
    if(value > node->value) {
        return Find(node->rightChild, value);
    }

    return node;
}
template <class T> int Treap<T>::Count(T value) {
    if(Find(root, value) != nullptr) {
        return 1;
    }
    else {
        return 0;
    }
}
template <class T> void Treap<T>::Insert(T value) {
    std::pair <Node<T> * , Node<T> * > split = Split(root, value);
    if(Find(root, value) == nullptr) {
        split.first = Merge(split.first, new Node<T>(value));
    }
    root = Merge(split.first, split.second);
}
template <class T> void Treap<T>::Erase(T value) {
    return;
}
template <>  void Treap<int>::Erase(int value) {
    std::pair<Node<int> * , Node<int> * > split0 = Split(root, value - 1);
    std::pair<Node<int> * , Node<int> * > split1 = Split(split0.second, value);
    delete split1.first;
    root = Merge(split0.first, split1.second);
    return;
}

template <class T> class TreapSet: public Treap<T> {};

}