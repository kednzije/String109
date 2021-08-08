#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    srand(time(NULL));
    freopen("Data.in", "w", stdout);
    cout << 1 << endl;
    int n = rand() % 15 + 1, m = rand() % n + rand() % n + 1;
    cout << n << ' ' << m << endl;
    for(int i = 1; i <= m; i++) {
        cout << rand() % n << ' ' << rand() % n << ' ' << rand() % 10 << endl;
    }
}