#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

int main() {
	freopen("Data.txt", "w", stdout);
	printf("10\n");
	srand(time(NULL));
	for(int i = 1; i <= 10; i++) {
		printf("100000\n");
		for(int j = 1; j <= 1e5; j++) {
			int x1 = rand() % 1000000000, x2 = rand() % 1000000000, x3 = rand() % 1000000000, x4 = rand() % 1000000000;
			while(x1 == x3 && x2 == x4) {
				x1 = rand() % 1000000000, x2 = rand() % 1000000000, x3 = rand() % 1000000000, x4 = rand() % 1000000000;
			}
			printf("%d %d %d %d\n", x1, x2, x3, x4);
		}
	}
}