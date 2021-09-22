// False

#include <iostream>
#include <utility>
#include <queue>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 1e5 + 10;
using ll = long long;
constexpr ll INF = 1e10 + 1e6;
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}

int n, m, k, head[MAXN];
struct Edge {
	int to, val, nxt;
} edges[MAXM];
void add_edge(int u, int v, int w, int i) {
	edges[i] = { v, w, head[u] };
	head[u] = i;
}

set <int> node_set;

ll ans;
ll dis[MAXN];
bool vis[MAXN];
void run_Dijkstra(int src_node) {
	memset(vis, false, sizeof(vis));
	priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> que;

	dis[src_node] = 0;
	que.push({ 0, src_node });

	while(!que.empty()) {
		int u = que.top().second;
		ll dis_u = que.top().first;
		que.pop();
		if(vis[u] || dis_u > dis[u]) {
			continue;
		}
		vis[u] = true;
		for(int i = head[u]; i; i = edges[i].nxt) {
			int v = edges[i].to, w = edges[i].val;
			if(dis[v] > dis[u] + w && w != -1) {
				dis[v] = dis[u] + w;
				que.push({ dis[v], v });
			}
		}
	}

	for(auto node: node_set) {
		if(dis[node] != 0) {
			ans = get_min(ans, dis[node]);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int case_i = 1; case_i <= T; case_i++) {
		memset(head, 0, sizeof(head));
		memset(edges, 0, sizeof(edges));
		node_set.clear();
		ans = INF;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w, i);
		}
		scanf("%d", &k);
		for(int i = 1; i <= k; i++) {
			int node;
			scanf("%d", &node);
			node_set.insert(node);
		}
		
		for(int u = 1; u <= n; u++) {
			if(!node_set.count(u)) {
				continue;
			}
			for(int i = head[u]; i; i = edges[i].nxt) {
				int v = edges[i].to;
				if(node_set.count(v)) {
					ans = get_min(ans, edges[i].val);
					edges[i].val = -1;
				}
			}
		}
		memset(dis, 0x7f, sizeof(dis));
		for(auto node: node_set) {
			run_Dijkstra(node);
		}

		printf("Case #%d: %lld\n", case_i, ans);
	}
}