#include <iostream>
#include <cstdio>
using namespace std;
using ll = long long;
constexpr ll MAXN = 1e5 + 10;
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 2; i <= n + 1; i++) {
			printf("%d ", i);
		}
		putchar('\n');
	}
	return 0;
}