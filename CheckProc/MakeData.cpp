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
    int n = rand() % 10 + 2;
    while(n--) {
        cout << rand() % 10 << ' ';
    }
}