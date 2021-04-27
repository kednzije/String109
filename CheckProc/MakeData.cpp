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
    int n = rand() % 100 + 1, m = rand() % (3 * n + 1);
    printf("1 %d %d\n", n, m);
    for(int i = 1; i <= m; i++) {
        printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    }
}