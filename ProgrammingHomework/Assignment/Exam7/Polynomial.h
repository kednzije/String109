#pragma once

class Polynomial {
public:
	virtual void addTerm(int coef, int power) = 0;
	virtual void setIthCoe(int i, int coef) = 0;
	virtual void setIthPow(int i, int power) = 0;
	virtual int getIthCoe(int i) = 0;
	virtual int getIthPow(int i) = 0;
	virtual int getSize() = 0;
};