#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	// freopen("data.txt", "w", stdout);
	// int n = 300;
	// printf("%d\n", n);
	// srand(time(NULL));
	// for(int i = 1; i <= n; i++) {
	// 	int x, y, z, v;
	// 	x = rand() % 1000, y = rand() % 1000, z = rand() % 1000, v = rand() % 1000;
	// 	printf("%d %d %d %d\n", x, y, z, v);
	// }

	freopen("1.txt", "w", stdout);
	int n = 1e5, m = 100;
	printf("%d %d\n", n, m);
	srand(time(NULL));
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % (int)(1e9 - 1) + 1);
	}
	printf("\n");
	for(int i = 1; i <= m; i++) {
		printf("%d\n", rand() % (int)(1e9 - 1) + 1);
	}
}