#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
const int MAXLEN = 105;

struct Monomial {
    int coef, ind;
    Monomial* next;
    Monomial() {
        coef = ind = 0;
        next = nullptr;
    }
    Monomial(const char* str, int l, int r) {
        coef = ind = 0;
        int i;
        for(i = l + 1; str[i] != 'x'; i++) {
            coef *= 10;
            coef += (str[i] - '0');
        }
        coef *= (str[l] == '+' ? 1 : -1);
        for(i += 2; i <= r; i++) {
            ind *= 10;
            ind += (str[i] - '0');
        }
        next = nullptr;
    }
    Monomial(int c, int i) {
        coef = c, ind = i;
        next = nullptr;
    }
    void operator += (const Monomial mono) {
        coef += mono.coef;
    }
    void operator -= (const Monomial mono) {
        coef -= mono.coef;
    }
    Monomial operator * (const Monomial mono) {
        Monomial res;
        res.coef = coef * mono.coef;
        res.ind = ind * mono.ind;
        return res;
    }
    void Display() {
        if(coef == 0) {
            return;
        }
        if(coef > 0) {
            cout << '+';
        }
        cout << coef << "x^" << ind;
        return;
    }
};

Monomial InitMonomial(char* str) {
    Monomial mono = Monomial();
    int i;
    for(i = 1; str[i] != 'x'; i++) {
        mono.coef *= 10;
        mono.coef += (str[i] - '0');
    }
    mono.coef *= (str[0] == '+' ? 1 : -1);
    for(i += 2; str[i] != '\0'; i++) {
        mono.ind *= 10;
        mono.ind += (str[i] - '0');
    }
    return mono;
}
void PrintMonomial(Monomial mono) {
    if(mono.coef == 0) {
        return;
    }
    cout << (mono.coef > 0 ? '+' : '-') << mono.coef << "x^" << mono.ind;
    return;
}

/*void Strcpy(char* to, char* from, int l, int r) {
    memset(to, 0, sizeof(to));
    for(int i = l; i <= r; i++) {
        to[i - l] = from[i];
    }
    return;
}*/

struct Polynomial {
    Monomial* head;
    Polynomial() {
        head = nullptr;
    }
    /*~Polynomial() {
        Monomial* curr = head, * temp;
        while(curr != nullptr) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
    }*/
    void Insert(Monomial* mono) {
        if(head == nullptr) {
            head = mono;
            return;
        }
        if(mono->ind > head->ind) {
            mono->next = head;
            head = mono;
        }
        else if(mono->ind == head->ind) {
            head->coef += mono->coef;
            delete mono;
        }
        else {
            Monomial* curr = head;
            while(curr->next != nullptr) {
                if(mono->ind > curr->next->ind) {
                    mono->next = curr->next;
                    curr->next = mono;
                    return;
                }
                if(mono->ind == curr->next->ind) {
                    curr->next->coef += mono->coef;
                    delete mono;
                    return;
                }
                else {
                    curr = curr->next;
                }
            }
            curr->next = mono;
        }
    }
    void Display() const {
        Monomial* curr = head;
        while(curr != nullptr) {
            curr->Display();
            curr = curr->next;
        }
        cout << endl;
    }
    Polynomial operator + (const Polynomial poly) const {
        Polynomial res = Polynomial();
        Monomial* curr = poly.head;
        while(curr != nullptr) {
            Monomial* mono = new Monomial(curr->coef, curr->ind);
            res.Insert(mono);
            curr = curr->next;
        }
        curr = head;
        while(curr != nullptr) {
            Monomial* mono = new Monomial(curr->coef, curr->ind);
            res.Insert(mono);
            curr = curr->next;
        }
        return res;
    }
    Polynomial operator - (const Polynomial poly) const {
        Polynomial res = Polynomial();
        Monomial* curr = poly.head;
        while(curr != nullptr) {
            Monomial* mono = new Monomial(-curr->coef, curr->ind);
            res.Insert(mono);
            curr = curr->next;
        }
        curr = head;
        while(curr != nullptr) {
            Monomial* mono = new Monomial(curr->coef, curr->ind);
            res.Insert(mono);
            curr = curr->next;
        }
        return res;
    }
    Polynomial operator * (const Polynomial poly) const {
        Polynomial res = Polynomial();
        for(Monomial* i = head; i != nullptr; i = i->next) {
            for(Monomial* j = poly.head; j != nullptr; j = j->next) {
                Monomial* mono = new Monomial(i->coef * j->coef, i->ind + j->ind);
                res.Insert(mono);
            }
        }
        return res;
    }
    void operator *= (const Polynomial poly) {
        Monomial* _head = head;
        head = nullptr;
        for(Monomial* i = _head; i != nullptr; i = i->next) {
            for(Monomial* j = poly.head; j != nullptr; j = j->next) {
                Monomial* mono = new Monomial(i->coef * j->coef, i->ind + j->ind);
                Insert(mono);
            }
        }
    }
};
Polynomial InitPolynomial(const char* str) {
    Polynomial poly = Polynomial();
    //char tempStr[MAXLEN];
    int l, r;
    l = r = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] =='\0') {
            r = i;
            //Strcpy(tempStr, str, l, r);
            Monomial* mono = new Monomial(str, l, r);
            poly.Insert(mono);
            l = i + 1;
        }
    }
    return poly;
}
void PrintPolynomial(const Polynomial &poly) {
    poly.Display();
    return;
}
Polynomial Add(const Polynomial &a, const Polynomial &b) {
    return a + b;
}
Polynomial Minus(const Polynomial &a, const Polynomial &b) {
    return a - b;
}
Polynomial Multiply(const Polynomial &a, const Polynomial &b) {
    return a * b;
}
Polynomial Power(const Polynomial &base, int exp) {
    Polynomial res = Polynomial();
    res.head = new Monomial(1, 0);
    Polynomial k = base * res;
    while(exp) {
        if(exp % 2) {
            res *= k;
        }
        k *= k;
        exp >>= 1;
    }
    return res;
}

#define DEBUG

#ifdef DEBUG
int main() {
    const int nMaxLen = 200;
    char str1[nMaxLen], str2[nMaxLen];
    cin >> str1 >> str2;
    Polynomial poly1 = InitPolynomial(str1), poly2 = InitPolynomial(str2);
    PrintPolynomial(Multiply(poly1, poly2));
    PrintPolynomial(Power(poly1, 2));
    return 0;
}
#endif
#ifndef DEBUG
#include "test.hpp"

int main() 
{
    test();
    return 0;
}
#endif