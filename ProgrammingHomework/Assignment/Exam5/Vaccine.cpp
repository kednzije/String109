#include "Vaccine.h"

#include <string>
using namespace std;

Vaccine::Vaccine(const string& name, int price, int number, int bound) {
    _name = name, _price = price, _number = number, _bound = bound;
}
string Vaccine::GetName() {
    return _name;
}
int Vaccine::GetPrice() {
    return _price;
}
int Vaccine::GetNumber() {
    return _number;
}
int Vaccine::GetBound() {
    return _bound;
}
int Vaccine::GetCost() {
    return _price * _number;
}
void Vaccine::AddNumber(int k) {
    _number += k;
}