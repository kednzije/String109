#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	freopen("data.txt", "w", stdout);
	cout << 1 << endl;
	int n = 2000;
	printf("%d\n", n);
	srand(time(NULL));
	for(int i = 1; i < n; i++) {
		printf("%d ", rand() % i + 1);
	}
	printf("\n");
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % (n - 1) + 1);
	}
	printf("\n");
}