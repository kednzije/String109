#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAX_NUM_LEN = 100;
inline int Max(int a, int b) {
    return a > b ? a : b;
}

struct Num {
    int len, digits[MAX_NUM_LEN];

    const int SCALE = 10;

    Num() {
        len = 0;
        memset(digits, 0, sizeof(digits));
    }
    void readNumber() {
        char digit = getchar();
        while(digit >= '0' && digit <= '9') {
            digits[len++] = (int)(digit - '0');
        }
    }
    void operator = (const int k) {
        for(int i = k; i; i /= SCALE) {
            digits[len++] = i % SCALE;
        }
    }
    void operator = (const Num num) {
        len = num.len;
        for(int i = 0; i < len; i++) {
            digits[i] = num.digits[i];
        }
    }
    void operator *= (const int k) {
        for(int i = 0; i < len; i++) {
            digits[i] *= k;
        }
        for(int i = 0; i < len; i++) {
            if(digits[i] >= SCALE) {
                digits[i + 1] += digits[i] / SCALE;
                digits[i] %= SCALE;
            }
        }
        while(digits[len] > 0 && len < MAX_NUM_LEN) {
            digits[len + 1] += digits[len] / SCALE;
            digits[len] %= SCALE;
            len++;
        }
    }
    void operator += (const Num num) {
        len = Max(len, num.len);
        for(int i = 0; i < len; i++) {
            digits[i] += num.digits[i];
            if(digits[i] >= SCALE) {
                digits[i + 1] += digits[i] / SCALE;
                digits[i] %= SCALE;
            }
        }
        while(digits[len] > 0 && len < MAX_NUM_LEN) {
            digits[len + 1] += digits[len] / SCALE;
            digits[len] %= SCALE;
            len++;
        }
    }
    void Output() {
        // if decimal
        for(int i = len - 1; i >= 0; i--) {
            putchar('0' + digits[i]);
        }
    }
};

int main() {
    int n;
    cin >> n;
    Num res = Num(), fac = Num();
    res = 0, fac = 1;
    for(int i = 1; i <= n; i++) {
        fac *= i;
        res += fac;
    }
    res.Output();
    return 0;
}