#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <cerrno>
#include <iterator>
#include <bitset>
using namespace std;
using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	ll num = 0, sign = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') {
			sign = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		num = num * 10 + (c - '0');
		c = getchar();
	}
	return sign * num;
}
constexpr ll MAXN = 1e7 + 50;

int buckets[MAXN];

int main() {
	int n, m, num, max_num = -1;
	// cin >> m >> n;
	// scanf("%d%d", &m, &n);
	m = input(), n = input();
	for(int i = 1; i <= n; i++) {
		// cin >> num;
		// scanf("%d", &num);
		num = input();
		buckets[num]++;

		max_num = get_max(max_num, num);
	}
	// buckets[k] counts the time number k appears.
	for(int k = max_num; k > 0; k--) {
		m -= buckets[k];
		if(m <= 0) { // meet the mth number
			// cout << k << endl;
			printf("%d\n", k);
			break;
		}
	}
	return 0;
}