// Order.h
#include <string>

class Order {
private:
    std::string name;
    double price;
    int quantity;
public:
    Order();
    Order(const Order& other);
    Order(std::string _name, double _price, int _quantity);

    void Display() const;
};

// Order.cpp
// #include "Order.h"
#include <string>
#include <iostream>
using namespace std;

Order::Order() {
    name = "";
    price = 0;
    quantity = 0;
}
Order::Order(const Order& other) {
    name = other.name, price = other.price, quantity = other.quantity;
}
Order::Order(std::string _name, double _price, int _quantity) {
    name = _name, price = _price, quantity = _quantity;
}

void Order::Display() const {
    cout << name << '\t' << price << '\t' << quantity << endl;
}

// OrderList.h
// #include "Order.h"

#include <vector>
#include <string>

class OrderList {
private:
    std::vector <Order> Orders;
    int orderCount;
public:
    OrderList();
    ~OrderList();
    OrderList(const OrderList& other);
    void* operator new(size_t size);
    void operator delete(void* ptr);

    bool Insert(std::string name, double price, int quantity);
    int GetOrderCount() const;
    void Display() const;
};

// OrderList.cpp
// #include "OrderList.h"

#include <vector>
#include <iostream>
using namespace std;

OrderList::OrderList() {
    Orders.clear();
    orderCount = 0;
}
OrderList::~OrderList() {
    Orders.clear();
    orderCount = 0;
}
OrderList::OrderList(const OrderList& other) {
    orderCount = other.orderCount;
    for(int i = 0; i < orderCount; i++) {
        Orders.push_back(Order(other.Orders[i]));
    }
}
void* OrderList::operator new(size_t size) {
    cout << "Create Successfully!" << endl;
    return ::new OrderList;
}
void OrderList::operator delete(void* ptr) {
    cout << "Delete Successfully!" << endl;
    delete ptr;
}

bool OrderList::Insert(string name, double price, int quantity) {
    if(orderCount == Orders.max_size()) {
        return false;
    }
    Orders.push_back(Order(name, price, quantity));
    orderCount++;
    cout << "Insert Successfully!" << endl;
    return true;
}
int OrderList::GetOrderCount() const {
    return orderCount;
}
void OrderList::Display() const {
    for(int i = 0; i < orderCount; i++) {
        Orders[i].Display();
    }
}

// Main.cpp
// #include "OrderList.h"
#include <iostream>
using namespace std;

int main() {
    OrderList* orderList = new OrderList;

    orderList->Insert("Merchandise0", 19.5, 3);
    orderList->Insert("Merchandise1", 3.9, 10);

    cout << orderList->GetOrderCount() << endl;
    orderList->Display();

    delete orderList;
    return 0;
}