#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
using ll = long long;

int main() {
	freopen("data.txt", "w", stdout);
	int t=5;
	printf("%d\n", t);
	while(t--) {
		ll n = 1e3;
		printf("%lld\n", n);
		for(int i = 1; i <= n; i++) {
			printf("%d ", rand() % int(1e9 - 1) + 1);
		}
		printf("\n");
		ll q = 1e5;
		printf("%lld\n", q);
		for(int i = 1; i <= q; i++) {
			int op = rand() % 3 + 1;
			while(op == 2) {
				op = rand() % 3 + 1;
			}
			int l = rand() % n + 1, r = rand() % n + 1;
			if(l > r) {
				swap(l, r);
			}
			printf("%d %d %d\n", op, l, r);
		}
	}
}