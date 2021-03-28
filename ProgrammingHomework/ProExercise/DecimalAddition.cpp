#include <iostream>
#include <cstring>
using namespace std;
const int MAXLEN = 105;
inline int Max(int a, int b) {
    return a > b ? a : b;
}

struct Number {
    const int BASE = 10;
    int intLen, decLen;
    int integerPart[MAXLEN], decimalPart[MAXLEN];
    Number() {
        intLen = decLen = 0;
        memset(integerPart, 0, sizeof(integerPart));
        memset(decimalPart, 0, sizeof(decimalPart));
    }
    Number(string s) {
        memset(integerPart, 0, sizeof(integerPart));
        memset(decimalPart, 0, sizeof(decimalPart));

        int ind = s.find('.');
        if(s.find('.') == s.npos) {
            ind = s.length();
        }
        intLen = ind, decLen = s.length() - ind - 1;
        if(decLen < 0) {
            decLen = 0;
        }
        for(int i = ind - 1;i >= 0;i--) {
            integerPart[ind - 1 - i] = s[i] - '0';
        }
        while(integerPart[intLen - 1] == 0 && intLen >= 0) {
            intLen--;
        }
        for(int i = ind + 1;i < s.length();i++) {
            decimalPart[i - ind - 1] = s[i] - '0';
        }
        while(decimalPart[decLen - 1] == 0 && decLen >= 0) {
            decLen--;
        }
    }
    void Output() {
        if(intLen <= 0 && decLen <= 0) {
            cout << '0' << endl;
            return;
        }
        for(int i = intLen - 1;i >= 0;i--) {
            cout << integerPart[i];
        }
        if(intLen <= 0) {
            cout << '0';
        }
        if(decLen > 0) {
            cout << '.';
        }
        for(int i = 0;i < decLen;i++) {
            cout << decimalPart[i];
        }
        cout << endl;
    }
    void operator += (const Number num) {
        intLen = Max(intLen, num.intLen);
        decLen = Max(decLen, num.decLen);
        for(int i = decLen - 1;i >= 0;i--) {
            decimalPart[i] += num.decimalPart[i];
            if(i > 0) {
                decimalPart[i - 1] += decimalPart[i] / BASE;
            }
            else {
                integerPart[0] += decimalPart[i] / BASE;
            }
            decimalPart[i] %= BASE;
        }
        while(decimalPart[decLen - 1] == 0 && decLen >= 0) {
            decLen--;
        }
        for(int i = 0;i < intLen;i++) {
            integerPart[i] += num.integerPart[i];
            integerPart[i + 1] += integerPart[i] / BASE;
            integerPart[i] %= BASE;
        }
        if(integerPart[intLen]) {
            intLen++;
        }
    }
};

int main() {
    int n;
    cin >> n;
    while(n--) {
        string a, b;
        cin >> a >> b;
        Number x = Number(a), y = Number(b);
        x += y;
        x.Output();
    }
    return 0;
}