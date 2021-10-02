#include <iostream>
using namespace std;
constexpr int MAXN = 5e4 + 10;
using ll = long long;

struct Edge {
	int to, val, nxt;
} edges[MAXN * 2];
int head[MAXN];
void add_edge(int u, int v, int w, int i) {
	edges[i] = { v, w, head[u] };
	head[u] = i;
}

ll max_len = -1;
void dfs(int node, ll len, int from) {
	max_len = max_len < len ? len : max_len;
	for(int i = head[node]; i; i = edges[i].nxt) {
		int to = edges[i].to;
		if(to == from) {
			continue;
		}
		dfs(to, len + edges[i].val, node);
	}
}

int main() {
	int n;
	cin >> n;
	ll sum = 0;
	for(int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w, i);
		add_edge(v, u, w, i + n);

		sum += w;
	}
	dfs(1, 0, 0);
	cout << sum * 2ll - max_len << endl;
}