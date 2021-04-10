// LinkNode.h
template <class T> class LinkNode;
template <class T> class LinkStack;

template <class T>
class LinkNode {
    friend class LinkStack<T>;
public:
    LinkNode();
private:
    T data;
    LinkNode<T>* next;
};

// LinkNode.cpp
// #include "LinkNode.h"

template <class T>
LinkNode<T>::LinkNode() {
    next = nullptr;
}

// LinkStack.h
// #include "LinkNode.h"

#include <iostream>

template <class T>
class LinkStack {
public:
    LinkStack();
    ~LinkStack();
    LinkStack(const LinkStack<T>& other);
    bool IsEmpty() const;
    bool Push(const T& x);
    bool Top(T& x);
    bool Pop(T& x);
    void OutPut(std::ostream& out) const;
private:
    LinkNode<T>* top;
    int size;
};

// LinkStack.cpp
// #include "LinkStack.h"

#include <iostream>
using namespace std;

template <class T>
LinkStack<T>::LinkStack() {
    top = nullptr;
    size = 0;
}
template <class T>
LinkStack<T>::~LinkStack() {
    T x;
    while(top != nullptr) {
        Pop(x);
    }
}
template <class T>
LinkStack<T>::LinkStack(const LinkStack<T>& other) {
    top = nullptr;
    size = other.size;
    for(LinkNode<T>* p = other.top; p != nullptr; p = p->next) {
        LinkNode<T>* node = new LinkNode<T>;
        node->data = p->data;
        if(top == nullptr) {
            top = node;
        }
        else {
            LinkNode<T>* pos = top;
            while(pos->next != nullptr) {
                pos = pos->next;
            }
            pos->next = node;
        }
    }
}
template <class T>
bool LinkStack<T>::IsEmpty() const {
    return top == nullptr;
}
template <class T> 
bool LinkStack<T>::Push(const T& x) {
    LinkNode<T>* p = new LinkNode<T>;
    if(p == nullptr) {
        return false;
    }
    p->data = x, p->next = top;
    top = p;
    size++;
    return true;
}
template <class T>
bool LinkStack<T>::Top(T& x) {
    if(IsEmpty()) {
        return false;
    }
    x = top->data;
    return true;
}
template <class T>
bool LinkStack<T>::Pop(T& x) {
    LinkNode<T>* p = top;
    if(IsEmpty()) {
        return false;
    }
    top = top->next;
    size--;
    x = p->data;
    delete p;
    return true;
}
template <class T>
void LinkStack<T>::OutPut(ostream& out) const {
    for(LinkNode<T>* p = top; p != nullptr; p = p->next) {
        out << p->data << endl;
    }
}

template <class T>
ostream& operator <<(ostream& out, const LinkStack<T>& sta) {
    sta.OutPut(out);
    return out;
}

// Main.cpp
template <class T>
void Print(const LinkStack<T>& sta) {
    LinkStack<T> cpy = sta;
    LinkStack<T> rev;
    while(!cpy.IsEmpty()) {
        T x;
        cpy.Pop(x);
        rev.Push(x);
    }
    cout << rev;
}

int main() {
    LinkStack<int> sta;
    sta.Push(1), sta.Push(2), sta.Push(3);

    cout << sta;
    cout << "========================" << endl;
    Print(sta);
    
    return 0;
}