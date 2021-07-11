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
    int n = rand() % 10 + 5;
    cout << n << endl;
    for(int i = 1; i <= n; i++) {
        int x = rand() % 10;
        if(!x) x++;
        cout << (rand() % 2 ? 1 : -1) * x << ' ';
    }
}