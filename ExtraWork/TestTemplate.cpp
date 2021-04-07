#include "FunctionTemplate.h"
#include <iostream>
using namespace std;

int main() {
    int a[10] = {0, 5, 6, 7, 45, 64, 15, 81, 24, 61};
    Sort(a, 10);
    for(int i = 0; i < 10; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
    char b[5] = "acdb";
    Sort(b, 4);
    cout << b << endl;
    return 0;
}