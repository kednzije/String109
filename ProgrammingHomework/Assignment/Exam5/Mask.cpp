#include "Mask.h"

#include <string>
using namespace std;

Mask::Mask(const string& name, int price, int number) {
    _name = name, _price = price, _number = number;
}
string Mask::GetName() {
    return _name;
}
int Mask::GetPrice() {
    return _price;
}
int Mask::GetNumber() {
    return _number;
}
int Mask::GetCost() {
    return _price * _number;
}
void Mask::AddNumber(int k) {
    _number += k;
}