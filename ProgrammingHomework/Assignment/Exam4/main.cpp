#include "Polynomial.h"

#include <iostream>
using namespace std;

int main() {
    // Polynomial poly1("x4+2x8-10x5+x2+1");
    // Polynomial poly2("2x2-5");
    // poly1.printHighest();
    // cout << endl;
    // // 输出 2x8
    // poly1.printExpression();
    // cout << endl;
    // // 输出 2x8-10x5+x4+x2+1
    // cout << poly2.computeValue(1);
    // cout << endl;
    // // 输出 -3
    // cout << poly1.getOriginal();
    // cout << endl;
    // // 输出 x4+2x8-10x5+x2+1
    // Polynomial poly3 = poly1 + poly2;
    // // Polynomial + 操作
    // poly3.printExpression();
    // cout << endl;
    // // 输出 2x8-10x5+x4+3x2-4
    // Polynomial poly4 = poly1 - poly2;
    // // Polynomial - 操作
    // poly4.printExpression();
    // cout << endl;
    // // 输出 2x8-10x5+x4-x2+6
    // Polynomial poly5 = poly1 - poly1;
    // poly5.printExpression();
    // cout << endl;
    // // 输出 0
    // Polynomial poly6(poly1);
    // poly6.printExpression();
    // cout << endl;
    // // 输出 2x8-10x5+x4+x2+1
    // cout << poly6.getOriginal();
    // cout << endl;
    // // 输出 x4+2x8-10x5+x2+1
    Polynomial poly1("-x4+2x8-10x5+x2+1");
    poly1.printHighest();
    cout << endl;
}