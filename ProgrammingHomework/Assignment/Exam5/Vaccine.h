#pragma once

#include <string>

class Vaccine {
private:
    std::string _name;
    int _price, _number, _bound;
public:
    Vaccine(const std::string& name, int price, int number, int bound);
    std::string GetName();
    int GetPrice();
    int GetNumber();
    int GetBound();
    int GetCost();

    void AddNumber(int k);
    operator int() { return GetCost(); }
};