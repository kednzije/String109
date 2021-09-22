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

int n, m, head[MAXN];
struct Edge {
	int to, val, nxt;
} edges[MAXM];
void add_edge(int u, int v, int w, int i) {
	edges[i] = { v, w, head[u] };
	head[u] = i;
}

int k;
set <int> node_set[3];

ll ans;
ll dis[MAXN];
bool vis[MAXN];
void run_Dijkstra(bool src_set) { // src_set -> node[n + src_set + 1], dst_set -> node[n + dst_set + 1]
	bool dst_set = !src_set;
	memset(dis, 0x7f, sizeof(dis));
	memset(vis, false, sizeof(vis));
	priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> que;
	
	for(auto node: node_set[src_set]) {
		dis[node] = 0;
		que.push({ 0, node });
	}

	while(!que.empty()) {
		int u = que.top().second;
		que.pop();

		if(vis[u]) {
			continue;
		}
		vis[u] = true;

		for(int i = head[u]; i; i = edges[i].nxt) {
			int v = edges[i].to, w = edges[i].val;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				que.push({ dis[v], v });
			}
		}
	}

	for(auto node: node_set[dst_set]) {
		ans = min(ans, dis[node]);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int case_i = 1; case_i <= T; case_i++) {
		memset(head, 0, sizeof(head));
		memset(edges, 0, sizeof(edges));
		for(int i = 0; i < 3; i++) {
			node_set[i].clear();
		}
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
			node_set[2].insert(node);
		}
		for(int bit_selector = 0; bit_selector < 20; bit_selector++) {
			node_set[0].clear(), node_set[1].clear();
			for(auto node: node_set[2]) {
				node_set[(node >> bit_selector) & 1].insert(node);
			}
			run_Dijkstra(0), run_Dijkstra(1);
		}
		printf("Case #%d: %lld\n", case_i, ans);
	}
}