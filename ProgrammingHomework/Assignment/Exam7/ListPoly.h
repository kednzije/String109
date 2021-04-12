#pragma once
#include "Polynomial.h"

struct Node {
	int coef;
	int power;
	Node *m_pre, *m_next;
	Node(int _coef, int _power) {
		m_pre = nullptr;
		m_next = nullptr;
		coef = _coef;
		power = _power;
	}
};

class ListPoly: public Polynomial {
private:
	// 指向链表头的指针
	Node* head;
public:
	// 默认构造函数
	ListPoly();
	// 析构函数，释放申请空间
	~ListPoly();
	// 拷⻉构造函数
	ListPoly(ListPoly const &polynomial);
	// 赋值操作符重载
	ListPoly& operator = (const ListPoly& p);
	// TODO：实现其他你需要实现的代码
	void addTerm(int coef, int power);
	void setIthCoe(int i, int coef);
	void setIthPow(int i, int power);
	int getIthCoe(int i);
	int getIthPow(int i);
	int getSize();
};