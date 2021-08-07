#include <iostream>
#include <cstring>
using namespace std;
// #define INT_MIN -2147483648
constexpr int MAXN = 16000 + 10;
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

int n, ans = INT_MIN, nums[MAXN], vis[MAXN], dp[MAXN][2];
void dfs(int node) {
	vis[node] = true;
	dp[node][0] = 0, dp[node][1] = nums[node];
	for(int i = head[node]; i != -1; i = edges[i].nxt) {
		int to = edges[i].to;
		if(!vis[to]) {
			dfs(to);
			dp[node][0] = max(dp[node][0], max(dp[to][0], dp[to][1]));
			dp[node][1] += (dp[to][1] > 0 ? dp[to][1] : 0);
		}
	}
	ans = max(ans, max(dp[node][0], dp[node][1]));
	return;
}

int main() {
	memset(head, -1, sizeof(head));
	cin >> n;
	bool all_neg = true;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		ans = max(ans, nums[i]);
		if(nums[i] >= 0) {
			all_neg = false;
		}
	}
	for(int i = 1; i <= n - 1; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(i, u, v);
		add_edge(i + n, v, u);
	}
	if(!all_neg) {
		dfs(1);
	}
	cout << ans << endl;
}