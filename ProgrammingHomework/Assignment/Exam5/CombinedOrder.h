#pragma once

#include "Mask.h"
#include "Vaccine.h"

#include <vector>
#include <string>
using namespace std;

template <class T>
class CombinedOrder {
private:
    vector <T> orders;
public:
    CombinedOrder();
    bool AddOrder(T& order);
    int GetTotalCost();
    T& operator[](int index);
    void Sort(bool (*func)(T, T));
};

template <class T>
CombinedOrder<T>::CombinedOrder() {
    orders.clear();
}
template <class T>
bool CombinedOrder<T>::AddOrder(T& order) {
    orders.push_back(order);
    return true;
}
template <>
bool CombinedOrder<Mask>::AddOrder(Mask& order) {
    for(int i = 0; i < orders.size(); i++) {
        if(orders[i].GetName() == order.GetName()) {
            orders[i].AddNumber(order.GetNumber());
            return true;
        }
    }
    orders.push_back(order);
    return true;
}
template <>
bool CombinedOrder<Vaccine>::AddOrder(Vaccine& order) {
    for(int i = 0; i < orders.size(); i++) {
        if(orders[i].GetName() == order.GetName()) {
            if(orders[i].GetBound() >= orders[i].GetNumber() + order.GetNumber()) {
                orders[i].AddNumber(order.GetNumber());
                return true;
            }
            else {
                return false;
            }
        }
    }
    if(order.GetNumber() <= order.GetBound()) {
        orders.push_back(order);
        return true;
    }
    else {
        return false;
    }
}
template <class T>
int CombinedOrder<T>::GetTotalCost() {
    int tot = 0;
    for(int i = 0; i < orders.size(); i++) {
        tot += (int)orders[i];
    }
    return tot;
}
template <class T>
T& CombinedOrder<T>::operator[](int index) {
    return orders[index];
}
template <class T>
void CombinedOrder<T>::Sort(bool (*func)(T, T)) {
    sort(orders.begin(), orders.end(), func);
}

#include <algorithm>
using namespace std;

template <class T>
bool IsLessThan(T t1, T t2) {
    return (int)t1 < (int)t2;
}
template <class T>
void SortOrder(CombinedOrder<T>& order) {
    order.Sort(IsLessThan);
}
