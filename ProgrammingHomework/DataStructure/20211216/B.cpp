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
constexpr ll MAXM = 5e3 + 10;

struct Edge {
	int to, nxt;
} edges[MAXM];
int head[MAXN], deg[MAXN];
void add_edge(int u, int v) {
	edges[++edges[0].to] = { v, head[u] };
	head[u] = edges[0].to;
}

bool vis[MAXN];

int main() {
	int n, m;
	// cin >> n >> m;
	n = input(), m = input();
	for(int i = 1; i <= m; i++) {
		int u, v;
		// cin >> u >> v;
		u = input(), v = input();
		u++, v++;
		add_edge(u, v);
		deg[v]++;
	}
	priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> que; // { deg, ind }
	for(int i = 1; i <= n; i++) {
		que.push({ deg[i], i });
	}
	bool good = true;
	while(!que.empty()) {
		while(!que.empty() && vis[que.top().second]) {
			que.pop();
		}
		if(que.empty()) {
			break;
		}
		pair <int, int> u = que.top();
		que.pop();
		if(u.first != 0) {
			good = false;
			break;
		}
		vis[u.second] = true;
		for(int i = head[u.second]; i; i = edges[i].nxt) {
			int v = edges[i].to;
			deg[v]--;
			que.push({ deg[v], v });
		}
	}
	cout << (good ? "True" : "False");
}