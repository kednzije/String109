// LinkedBinTree.h
template <class T> class LinkedBinTree;

template <class T>
class LinkedNode {
    friend class LinkedBinTree<T>;

    T m_data;
    LinkedNode <T> * m_pLeftChild, * m_pRightChild;
public:
    LinkedNode() {
        m_pLeftChild = m_pRightChild = nullptr;
    }
    LinkedNode(const T& x) {
        m_pLeftChild = m_pRightChild = nullptr;
        m_data = x;
    }
};

template <class T>
class LinkedBinTree {
    LinkedNode<T> * m_pRoot;
public:
    LinkedBinTree();
    ~LinkedBinTree();
    bool isEmpty();
    void Clear();
    void Clear(LinkedNode<T> * pNode);
    LinkedNode<T> * GetRoot();
    LinkedNode<T> * InsertLeftChild(LinkedNode<T> * pNode, const T& x);
    LinkedNode<T> * InsertRightChild(LinkedNode<T> * pNode, const T& x);
    bool ModifyNodeValue(LinkedNode<T> * pNode, const T& x);
    bool GetNodeValue(LinkedNode<T> * pNode, T& x);
    LinkedNode<T> * GetLeftChild(LinkedNode<T> * pNode);
    LinkedNode<T> * GetRightChild(LinkedNode<T> * pNode);

    void InOrderTraverse();
    void InOrderTraverse(LinkedNode<T> * pNode);
    bool Insert(const T& x);
};

// LinkedBinTree.cpp
// #include "LinkedBinTree.h"

#include <iostream>
using namespace std;

template <class T>
LinkedBinTree<T>::LinkedBinTree() {
    m_pRoot = nullptr;
}
template <class T>
LinkedBinTree<T>::~LinkedBinTree() {
    Clear(m_pRoot);

    m_pRoot = nullptr;
}
template <class T>
bool LinkedBinTree<T>::isEmpty() {
    return m_pRoot == nullptr;
}
template <class T>
void LinkedBinTree<T>::Clear() {
    ~LinkedBinTree();
}
template <class T>
void LinkedBinTree<T>::Clear(LinkedNode<T> * pNode) {
    if(pNode == nullptr) {
        return;
    }
    Clear(pNode->m_pLeftChild);
    Clear(pNode->m_pRightChild);
    delete pNode;
}
template <class T>
LinkedNode<T> * LinkedBinTree<T>::InsertLeftChild(LinkedNode<T> * pNode, const T& x) {
    if(pNode == nullptr) {
        return nullptr;
    }
    LinkedNode<T> * pNewNode = new LinkedNode<T>(x);
    if(pNewNode == nullptr) {
        return nullptr;
    }
    pNode->m_pLeftChild = pNewNode;
    return pNewNode;
}
template <class T>
LinkedNode<T> * LinkedBinTree<T>::InsertRightChild(LinkedNode<T> * pNode, const T& x) {
    if(pNode == nullptr) {
        return nullptr;
    }
    LinkedNode<T> * pNewNode = new LinkedNode<T>(x);
    if(pNewNode == nullptr) {
        return nullptr;
    }
    pNode->m_pRightChild = pNewNode;
    return pNewNode;
}
template <class T>
bool LinkedBinTree<T>::ModifyNodeValue(LinkedNode<T> * pNode, const T& x) {
    if(pNode == nullptr) {
        return false;
    }
    pNode->m_data = x;
    return true;
}
template <class T>
bool LinkedBinTree<T>::GetNodeValue(LinkedNode<T> * pNode, T& x) {
    if(pNode == nullptr) {
        return false;
    }
    x = pNode->m_data;
    return true;
}
template <class T>
LinkedNode<T> * LinkedBinTree<T>::GetLeftChild(LinkedNode<T> * pNode) {
    if(pNode == nullptr) {
        return nullptr;
    }
    return pNode->m_pLeftChild;
}
template <class T>
LinkedNode<T> * LinkedBinTree<T>::GetRightChild(LinkedNode<T> * pNode) {
    if(pNode == nullptr) {
        return nullptr;
    }
    return pNode->m_pRightChild;
}
template <class T>
void LinkedBinTree<T>::InOrderTraverse() {
    InOrderTraverse(m_pRoot);
    cout << endl;
}
template <class T>
void LinkedBinTree<T>::InOrderTraverse(LinkedNode<T> * pNode) {
    if(pNode == nullptr) {
        return;
    }
    InOrderTraverse(pNode->m_pLeftChild);
    cout << pNode->m_data << ' ';
    InOrderTraverse(pNode->m_pRightChild);
}
template <class T>
bool LinkedBinTree<T>::Insert(const T& x) {
    if(isEmpty()) {
        m_pRoot = new LinkedNode<T>(x);;
        return true;
    }
    LinkedNode<T> * pNode = m_pRoot;
    while(pNode != nullptr) {
        if(x < pNode->m_data) {
            if(pNode->m_pLeftChild == nullptr) {
                pNode->m_pLeftChild = new LinkedNode<T>(x);
                break;
            }
            else {
                pNode = pNode->m_pLeftChild;
            }
        }
        if(x > pNode->m_data) {
            if(pNode->m_pRightChild == nullptr) {
                pNode->m_pRightChild = new LinkedNode<T>(x);
                break;
            }
            else {
                pNode = pNode->m_pRightChild;
            }
        }
    }
    return true;
}

// main.cpp
// #include "LinkedBinTree"

#include <iostream>
using namespace std;

int main() {
    LinkedBinTree <int> tree;
    tree.Insert(43);
    tree.InOrderTraverse();
    tree.Insert(56);
    tree.InOrderTraverse();
    tree.Insert(37);
    tree.InOrderTraverse();
    tree.Insert(28);
    tree.InOrderTraverse();
    tree.Insert(17);
    tree.InOrderTraverse();
    tree.Insert(39);
    tree.InOrderTraverse();
    tree.Insert(22);
    tree.InOrderTraverse();
    tree.Insert(70);
    tree.InOrderTraverse();
}