#pragma once
#include "Polynomial.h"

struct Item {
	int coef;
	int power;
	Item() {}
	Item(int a, int b) { coef = a; power = b; }
};

class ArrayPoly: public Polynomial {
private:
	// 使⽤Item的数组实现，不允许使⽤stl中的模版实现
	Item* item_array;
	int size, ind;
public:
	// 默认构造函数
	ArrayPoly();
	// 拷⻉构造函数
	ArrayPoly(ArrayPoly const& a);
	// 析构函数
	~ArrayPoly();
	// 赋值操作符重载
	ArrayPoly& operator = (const ArrayPoly& p);
	// TODO：实现其他你需要实现的代码
	void addTerm(int coef, int power);
	void setIthCoe(int i, int coef);
	void setIthPow(int i, int power);
	int getIthCoe(int i);
	int getIthPow(int i);
	int getSize();
};