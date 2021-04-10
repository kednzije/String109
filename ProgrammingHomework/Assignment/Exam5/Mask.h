#pragma once

#include <string>

class Mask {
private:
    std::string _name;
    int _price, _number;
public:
    Mask(const std::string& name, int price, int number);
    std::string GetName();
    int GetPrice();
    int GetNumber();
    int GetCost();

    void AddNumber(int k);
    operator int() { return GetCost(); }
};