#include "Polynomial.h"

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

// int* convertString2Int(const char* char_array)
// 1. 将char_array指向的字符串数组转换为对应的多项式表达，用int数组表示
// 2. 返回长度为100的int型数组，每个数组元素代表对应指数项的次数
//   例如，x4 + 3x2 + 1 这一多项式返回的数组中，下标为0处的元素为1，代表+1这个项；下标为2的元素为3，代表+3x2这个项；
//        下标为4的元素为1，代表x4这个项
// 3. 函数仅供本次上机使用，在本次上机中不会影响结果，应用在其他场景不保证正确性。

void createItem(string s, int* array) {
    if(s == "")
        return;
    if(s[0] == '+')
        s.erase(s.begin());
    if(s[0] == 'x')
        s.insert(s.begin(), '1');
    else if(s[0] == '-' && s[1] == 'x')
        s.insert(s.begin() + 1, '1');
    
    int coefficent = 0;
    int power = 0;
    int index = 0;
    while(index < s.size() && s[index] != 'x') {
        index++;
    }
    coefficent = atoi(s.substr(0, index).c_str());
    if(index < s.size() - 1) {
        power = atoi(s.substr(index + 1, s.size() - index).c_str());
    } else if(index == s.size() - 1) {
        power = 1;
    } else {
        power = 0;
    }
    array[power] += coefficent;
}

int* convertString2Int(const char* c) {
    int* array = new int[100];
    for(int i = 0; i < 100; i++)
        array[i] = 0;
    string str(c);
    if(str == "")
        return array;
    int preIndex = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '+' || str[i] == '-'){
            createItem(str.substr(preIndex, i - preIndex), array);
            preIndex = i;
        }
    }
    createItem(str.substr(preIndex, str.size() - preIndex), array);
    return array;
}

Polynomial::Polynomial(const char* str) {
    original_expr = new char[strlen(str) + 1];
    strcpy(original_expr, str);
    coefficient_array = convertString2Int(original_expr);
}
Polynomial::Polynomial(const Polynomial& poly) {
    original_expr = new char[strlen(poly.original_expr) + 1];
    strcpy(original_expr, poly.original_expr);
    coefficient_array = convertString2Int(original_expr);
}
Polynomial::~Polynomial() {
    if(coefficient_array != NULL) {
        delete[] coefficient_array;
        coefficient_array = NULL;
    }
    if(original_expr != NULL) {
        delete[] original_expr;
        original_expr = NULL;
    }
}
char* Polynomial::getOriginal() {
    return original_expr;
}
void Polynomial::printHighest() {
    for(int i = 99; i >= 0; i--) {
        if(coefficient_array[i] != 0) {
            if(coefficient_array[i] == -1 && i) {
                cout << '-';
            }
            else if(coefficient_array[i] != 1 || i == 0) {
                cout << coefficient_array[i];
            }
            if(i > 1) {
                cout << 'x' << i;
            }
            else if(i == 1) {
                cout << 'x';
            }
            return;
        }
    }
    cout << 0;
}
void Polynomial::printExpression() {
    bool isHighest = true;
    for(int i = 99; i >= 0; i--) {
        if(coefficient_array[i] != 0) {
            if(isHighest) {
                isHighest = false;
            }
            else if(coefficient_array[i] > 0) {
                cout << '+';
            }
            if(coefficient_array[i] == -1 && i) {
                cout << '-';
            }
            else if(coefficient_array[i] != 1 || i == 0) {
                cout << coefficient_array[i];
            }
            if(i > 1) {
                cout << 'x' << i;
            }
            else if(i == 1) {
                cout << 'x';
            }
        }
    }
    if(isHighest) {
        cout << 0;
    }
}
int Polynomial::computeValue(int x1) {
    int val = 0;
    for(int i = 99; i >= 0; i--) {
        val += coefficient_array[i] * pow(x1, i);
    }
    return val;
}
Polynomial Polynomial::operator+ (const Polynomial& poly) const {
    Polynomial res = poly;
    for(int i = 0; i < 100; i++) {
        res.coefficient_array[i] += coefficient_array[i];
    }
    string str;
    str = original_expr;
    // str = str + '+' + poly.original_expr;
    if(poly.original_expr[0] == '-') {
        str = str + poly.original_expr;
    }
    else {
        str = str + '+' + poly.original_expr;
    }
    // res.original_expr = str.data();
    res.original_expr = new char[str.length() + 1];
    strcpy(res.original_expr, str.data());
    return res;
}
Polynomial Polynomial::operator- (const Polynomial& poly) const {
    Polynomial res = Polynomial(*this);
    for(int i = 0; i < 100; i++) {
        res.coefficient_array[i] -= poly.coefficient_array[i];
    }
    string str;
    str = original_expr;
    char* str1 = new char[strlen(poly.original_expr) + 1];
    strcpy(str1, poly.original_expr);
    for(int i = 0; i < strlen(str1); i++) {
        if(str1[i] == '+') {
            str1[i] = '-';
        }
        else if(str1[i] == '-') {
            str1[i] = '+';
        }
    }
    // str = str + str1;
    if(str1[0] == '+') {
        str = str + str1;
    }
    else {
        str = str + '-' + str1;
    }
    // res.original_expr = str.data();
    res.original_expr = new char[str.length() + 1];
    strcpy(res.original_expr, str.data());
    return res;
}
void Polynomial::operator= (const Polynomial& poly) {
    original_expr = new char[strlen(poly.original_expr) + 1];
    strcpy(original_expr, poly.original_expr);
    coefficient_array = convertString2Int(original_expr);
}
bool Polynomial::operator== (const Polynomial& poly) const {
    Polynomial p = (*this) - poly;
    for(int i = 0; i < 100; i++) {
        if(p.coefficient_array[i]) {
            return false;
        }
    }
    return true;
}