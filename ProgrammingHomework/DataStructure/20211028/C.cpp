#include <iostream>
#include <cstring>
using namespace std;
#define INT_MIN -2147483647
constexpr int MAXN = 16000;
inline int min(int a, int b) {
	return a < b ? a : b;
}
inline int max(int a, int b) {
	return a > b ? a : b;
}

struct Edge {
	int to, nxt;
} edges[MAXN * 2];
int head[MAXN];
void add_edge(int i, int from, int to) {
	edges[i] = Edge{to, head[from]};
	head[from] = i;
}

int n, nums[MAXN];
int dfs(int node, bool inside, int from) {
	int ans;
	if(inside) {
		ans = nums[node];
		for(int i = head[node]; i != -1; i = edges[i].nxt) {
			if(edges[i].to != from) {
				int subans = dfs(edges[i].to, inside, node);
				if(subans > 0) {
					ans += subans;
				}
			}
		}
	}
	else {
		ans = 0;
		for(int i = head[node]; i != -1; i = edges[i].nxt) {
			if(edges[i].to != from) {
				ans = max(ans, max(dfs(edges[i].to, true, node), dfs(edges[i].to, false, node)));
			}
		}
	}
	return ans;
}

int main() {
	memset(head, -1, sizeof(head));
	cin >> n;
	int ans = INT_MIN;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		ans = max(ans, nums[i]);
	}
	for(int i = 1; i <= n - 1; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(i, u, v);
		add_edge(i + n, v, u);
	}
	ans = max(dfs(1, true, 0), dfs(1, false, 0));
	cout << ans << endl;
}