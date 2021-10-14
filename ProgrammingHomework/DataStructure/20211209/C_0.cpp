#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e3 + 50;
using ll = long long;
constexpr ll INF = 1e9 + 7;
ll get_min(ll a, ll b) {
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

ll n, m, dis[MAXN][MAXN];

int main() {
	// ios::sync_with_stdio(false);
	// cin >> n >> m;
	n = input(), m = input();
	memset(dis, 0x3f, sizeof(dis));
	for(int i = 1; i <= n; i++) {
		dis[i][i] = 0;
	}
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		// cin >> u >> v >> w;
		u = input(), v = input(), w = input();
		dis[u][v] = get_min(dis[u][v], w);
	}
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				dis[i][j] = get_min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += dis[1][i] + dis[i][1];
	}
	cout << sum << endl;
}