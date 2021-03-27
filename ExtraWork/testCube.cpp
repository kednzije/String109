#include "Cube.h"
#include <iostream>

using namespace std;

int Cube::numOfObject = 0;

Cube::Cube() {
    m_x = 0;
    numOfObject++;
}
Cube::~Cube() {
    numOfObject--;
}
void Cube::set(double x) {
    m_x = x;
}
double Cube::getVolume() {
    return m_x * m_x * m_x;
}
void Cube::displayNumOfObject() {
    cout << numOfObject << endl;
}

void Test() {
    Cube cube0;
    cube0.set(2.0);
    cout << cube0.getVolume() << endl;
    Cube::displayNumOfObject();
}

int main() {
    Cube::displayNumOfObject();
    Test();
    Cube::displayNumOfObject();
    return 0;
}