#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	freopen("Num.txt", "w", stdout);
	long long n = 1e18 + 5;
	for(long long i = 1; i <= n; i++) {
		for(long long j = i; j <= n; j++) {
			if((i * i + j * j) % (i * j + 1ll) == 0) {
				printf("%lld, %lld, \n", i, j);
			}
		}
	}
}