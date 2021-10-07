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
constexpr ll MAXN = 1e3 + 50;

int path[MAXN], dis[MAXN][MAXN];

int main() {
	int n, m, src, dst;
	n = input(), m = input(), src = input(), dst = input();

	memset(dis, 0x3f, sizeof(dis));
	for(int i = 0; i < n; i++) {
		dis[i][i] = 0;
	}

	for(int i = 1; i <= m; i++) {
		int len = input(), cost;
		for(int j = 1; j <= len; j++) {
			path[j] = input();
		}
		for(int j = 1; j < len; j++) {
			cost = input();
			dis[path[j]][path[j + 1]] = get_min(dis[path[j]][path[j + 1]], cost);
			dis[path[j + 1]][path[j]] = get_min(dis[path[j + 1]][path[j]], cost);
		}
	}
	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				dis[i][j] = get_min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	printf("%d\n", dis[src][dst]);
	return 0;
}