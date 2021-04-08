// LinkList.h
template <class T> class LinkNode;
template <class T> class LinkList;

template <class T>
class LinkNode {
    // template <class T>
    // friend class LinkList;
    friend class LinkList <T>;
public:
    LinkNode() {
        next = 0;
    }
private:
    T data;
    LinkNode <T> *next;
};

template <class T>
class LinkList {
public:
    LinkList();
    //~LinkList();
    LinkList <T> &Insert(int k, const T& x);
    bool IsEmpty() const;
    int GetLength() const;
    bool GetData(int k, T& x);
    bool ModifyData(int k, const T& x);
    // int Find(const T& x);
    // LinkList<T> &DeleteByIndex(int k, T &x);
    // LinkList<T> &DeleteByKey(const T &x, T &y);
    // void OutPut(ostream& out);
private:
    LinkNode<T> *head;
};

// LinkList.cpp
#include <iostream>
using namespace std;

template<class T>
LinkList<T>::LinkList() {
    head = new LinkNode<T> ();
}
// template<class T>
// LinkList<T>::~LinkList() {
//     T x;
//     int len = GetLength();
//     for(int i = len; i >= 1; i--) {
//         DeleteByIndex(i, x);
//     }
//     delete head;
// }
template <class T>
LinkList<T> &LinkList<T>::Insert(int k, const T& x) {
    LinkNode<T> *p = head;
    LinkNode<T> *newNode = new LinkNode<T>;
    newNode->data = x;

    int len = GetLength();
    if(k < 1 || k > len + 1) {
        cout << "元素下标越界，添加元素失败";
    }
    else {
        for(int i = 1; i < k; i++) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }

    return *this;
}
template <class T>
bool LinkList<T>::IsEmpty() const {
    return head->next == NULL;
}
template <class T>
int LinkList<T>::GetLength() const {
    int length = 0;
    LinkNode<T> *p = head->next;
    while(p) {
        length++;
        p = p->next;
    }
    return length;
}
template <class T>
bool LinkList<T>::GetData(int k, T& x) {
    LinkNode<T> *p = head->next;
    int index = 1;
    if(k < 1 || k > GetLength()) {
        return false;
    }
    while(p != NULL && index < k) {
        index++;
        p = p->next;
    }
    if(p == NULL) {
        return false;
    }
    else {
        x = p->data;
        return true;
    }
}
template <class T>
bool LinkList<T>::ModifyData(int k, const T& x) {
    LinkNode<T> *p = head->next;
    int index = 1;
    if(k < 1 || k > GetLength()) {
        return false;
    }
    while (p != NULL && index < k) {
        index++;
        p = p->next;
    }

    if(p == NULL) {
        return false;
    }
    else {
        p->data = x;
        return true;
    }
}

// Merge.cpp
template <class T>
void Merge(LinkList<T> Link1, LinkList<T> Link2, LinkList<T> &Link3) {
    int i = 1, j = 1;
    while(i <= Link1.GetLength() || j <= Link2.GetLength()) {
        T x,y;
        bool _x = Link1.GetData(i, x), _y = Link2.GetData(j, y);
        if(!_x || y < x) {
            Link3.Insert(Link3.GetLength() + 1, y);
            j++;
            continue;
        }
        if(!_y || x < y) {
            Link3.Insert(Link3.GetLength() + 1, x);
            i++;
            continue;
        }
    }
}

// Main.cpp
#include <iostream>
using namespace std;

int main() {
    LinkList <int> l1;
    LinkList <int> l2;
    l1.Insert(1, 7), l1.Insert(1, 5),l1.Insert(1, 3),l1.Insert(1, 1);
    l2.Insert(1, 8), l2.Insert(1, 6),l2.Insert(1, 4),l2.Insert(1, 2);
    LinkList <int> l3;
    Merge(l1, l2, l3);
    for(int i = 1; i <= l3.GetLength(); i++) {
        int k;
        l3.GetData(i, k);
        cout << k << ' ';
    }
    cout << endl;
    return 0;
}