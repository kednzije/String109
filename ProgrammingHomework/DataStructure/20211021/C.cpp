#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 5e4 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}

int head[MAXN];
struct Edge {
	int u, v, nxt;
} edges[MAXN * 2];

void addEdge(int i, int u, int v) {
	edges[i] = Edge{u, v, head[u]};
	head[u] = i;
}

int steps[MAXN];
void dfs1(int pos, int step) {
	steps[pos] = step;
	for(int i = head[pos]; i != -1; i = edges[i].nxt) {
		int dest = edges[i].v;
		if(steps[dest] == -1) {
			dfs1(dest, step + 1);
		}
	}
}

int ans = 0;
bool vis[MAXN];
void dfs2(int pos, int step) {
	vis[pos] = true;
	if(step >= steps[pos]) {
		ans = max(ans, step);
		return;
	}
	ans = max(ans, steps[pos]);
	for(int i = head[pos]; i != -1; i = edges[i].nxt) {
		int dest = edges[i].v;
		if(!vis[dest]) {
			dfs2(dest, step + 1);
		}
	}
}

int main() {
	memset(head, -1, sizeof(head));
	memset(steps, -1, sizeof(steps));
	int x, y, n;
	cin >> n >> x >> y;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		addEdge(i, u, v), addEdge(i + n, v, u);
	}
	dfs1(x, 0);
	dfs2(y, 0);
	cout << ans;
}