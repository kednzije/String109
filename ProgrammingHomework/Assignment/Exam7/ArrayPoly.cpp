#include "ArrayPoly.h"

#include <cstring>

ArrayPoly::ArrayPoly() {
	item_array = new Item[10];
	size = 10, ind = 0;
	for(int i = 0; i < size; i++) {
		item_array[i] = Item(0, 0);
	}
}
ArrayPoly::ArrayPoly(ArrayPoly const &a) {
	delete[] item_array;
	item_array = new Item[a.size];
	size = a.size, ind = a.ind;
	for(int i = 0; i < size; i++) {
		item_array[i] = a.item_array[i];
	}
}
ArrayPoly::~ArrayPoly() {
	delete item_array;
	size = 0, ind = -1;
}
ArrayPoly& ArrayPoly::operator= (const ArrayPoly& p) {
	delete item_array;
	item_array = new Item[p.size];
	size = p.size, ind = p.ind;
	for(int i = 0; i < size; i++) {
		item_array[i] = p.item_array[i];
	}
	return *this;
}
void ArrayPoly::addTerm(int coef, int power) {
	if(ind == size) {
		Item* item_array_new = new Item[size + 10];
		for(int i = 0; i < ind; i++) {
			item_array_new[i] = item_array[i];
		}
		delete item_array;
		item_array = item_array_new;
		size += 10;
	}
	for(int i = 0; i < ind; i++) {
		if(item_array[i].power == power) {
			item_array[i].coef += coef;
			if(!item_array[i].coef) {
				ind--;
				for(int j = i; j < ind; j++) {
					item_array[j] = item_array[j + 1];
				}
			}
			return;
		}
	}
	if(coef) {
		item_array[ind++] = Item(coef, power);
	}
}
void ArrayPoly::setIthCoe(int i, int coef) {
	item_array[i].coef = coef;
	// if(!item_array[i].coef) {
	// 	ind--;
	// 	for(int j = i; j < ind; j++) {
	// 		item_array[j] = item_array[j + 1];
	// 	}
	// }
}
void ArrayPoly::setIthPow(int i, int power) {
	item_array[i].power = power;
	// 
}
int ArrayPoly::getIthCoe(int i) {
	return item_array[i].coef;
}
int ArrayPoly::getIthPow(int i) {
	return item_array[i].power;
}
int ArrayPoly::getSize() {
	return ind;
}