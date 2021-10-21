#include <bits/stdc++.h>
using namespace std;

using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	static ll num, sign;
	static char c;
	num = 0, sign = 1;
	c = getchar();
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
constexpr ll MAXN = 1e5 + 10;

int h[MAXN], ans[MAXN];

int main() {
	int n = input();
	for(int i = 1; i <= n; i++) {
		h[i] = input();
	}
	priority_queue <int, vector <int>, less <int>> l;
	priority_queue <int, vector <int>, greater <int>> r;
}