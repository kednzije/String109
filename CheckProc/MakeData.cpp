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
    int n = rand() % 105 + 5, a = rand() % (n - 2) + 1, b = rand() % (n - a - 1) + 1 , c = n - a - b;
    printf("%d %d %d %d\n", n, a, b, c);
    for(int i = 1; i <= n; i++) {
        printf("%d %d %d\n", rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1);
    }
}