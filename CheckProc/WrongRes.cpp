#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;
constexpr int MAXK = 1e3 + 10;
using ll = long long;

inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

int n, m, k, cnt, depth[MAXN], fa[MAXN];
struct Edge {
	int to;
	ll val;
};
struct Edge_Full {
	int from, to;
	ll val;
	bool operator < (const Edge_Full& other) const {
		return val < other.val;
	}
};
vector <Edge> edges[MAXN];
// vector <int> vertices[MAXN];
vector <Edge_Full> parts[MAXN];
map <pair <int, int>, ll> edges_map;
#ifdef NEED_SINGLE_VERTICE
bool in_a_circle[MAXN];
#endif

/**
 * @brief Get a circle from 'x' to 'y', 'y' is the ancestor of 'x'
 * 
 * @param x index of a node
 * @param y index of a node
 */
void get_circle(int x, int y) {
	if(depth[x] < depth[y]) {
		return;
	}
	cnt++;
	// vertices[cnt].push_back(y);
	parts[cnt].push_back({ x, y, edges_map[{ x, y }] + edges_map[{ y, x }] });
	edges_map.erase(make_pair(x, y)), edges_map.erase(make_pair(y, x));
#ifdef NEED_SINGLE_VERTICE
	in_a_circle[y] = true;
#endif
	for (; x != y; x = fa[x]) {
		// vertices[cnt].push_back(x);
		parts[cnt].push_back({ x, fa[x], edges_map[{ x, fa[x] }] + edges_map[{ fa[x], x }] });
		edges_map.erase(make_pair(x, fa[x])), edges_map.erase(make_pair(fa[x], x));
#ifdef NEED_SINGLE_VERTICE
		in_a_circle[x] = true;
#endif
	}
}

void dfs(int x, int from) {
	fa[x] = from, depth[x] = depth[from] + 1;
	for (Edge edge : edges[x]) {
		if (edge.to != from) {
			int y = edge.to;
			if (depth[y]) {
				get_circle(x, y);
			}
			else {
				dfs(y, x);
			}
		}
	}
#ifdef NEED_SINGLE_VERTICE
	if(!in_a_circle[x]) {
		get_circle(x, x);
	}
#endif
}

unsigned short dp_from[MAXN][MAXK];
ll dp[2][MAXK];

int *colors = fa;
void paint(int pos, int color) {
	colors[pos] = color;
	for(auto &edge: edges[pos]) {
		if(!colors[edge.to]) {
			paint(edge.to, color);
		}
	}
}

int main() {
	freopen("Data.in", "r", stdin);
    freopen("WrongRes.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int ind = 1; ind <= T; ind++) {
		// cin >> n >> m >> k;
		scanf("%d%d%d", &n, &m, &k);
		if(m == 0) {
			printf("Case %d: 0\n", ind);
			for(int i = 1; i <= n; i++) {
				// cout << min(i, k) << ' ';
				printf("%d ", min(i, k));
			}
			continue;
		}

		for(int i = 1; i <= n; i++) {
			edges[i].clear();
			// vertices[i].clear();
			parts[i].clear();
		}
		edges_map.clear();
		for(int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			edges[u].push_back(Edge{ v, w });
			edges[v].push_back(Edge{ u, w });
			if(edges_map.find(make_pair(u, v)) != edges_map.end()) {
				edges_map[{ u, v }] += w;
			}
			else if(edges_map.find(make_pair(v, u)) != edges_map.end()) {
				edges_map[{ v, u }] += w;
			}
			else {
				edges_map[make_pair(u, v)] = w;
			}
		}

		cnt = 0;
		memset(depth, 0, sizeof(depth));
		memset(fa, 0, sizeof(fa));
		dfs(1, 0);
		for(auto &edge: edges_map) {
			parts[++cnt].push_back({ edge.first.first, edge.first.second, edge.second });
		}
		for(int i = 1; i <= cnt; i++) {
			sort(parts[i].begin(), parts[i].end());
		}

		memset(dp_from, 0, sizeof(dp_from));
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = dp[0][1] = 0;
		for(int i = 1; i <= cnt; i++) {
			int now = i % 2, pre = (i + 1) % 2;
			dp[now][0] = LLONG_MAX / 2, dp[now][1] = 0;
			dp_from[now][0] = 0, dp_from[now][1] = 1;
			for(int j = 2; j <= k; j++) {
				dp[now][j] = dp[pre][j];
				dp_from[i][j] = j;
				if(parts[i].size() == 1) {
					// dp[now][j] = min(dp[now][j], dp[pre][j - 1] + parts[i][0]);
					if(dp[now][j] > dp[pre][j - 1] + parts[i][0].val) {
						dp[now][j] = dp[pre][j - 1] + parts[i][0].val;
						dp_from[i][j] = j - 1;
					}
				}
				else {
					ll sum = parts[i][0].val;
					for(int num = 1; num < parts[i].size(); num++) {
						sum += parts[i][num].val;
						if(j - num < 0) {
							break;
						}
						// dp[now][j] = min(dp[now][j], dp[pre][j - num] + sum);
						if(dp[now][j] > dp[pre][j - num] + sum) {
							dp[now][j] = dp[pre][j - num] + sum;
							dp_from[i][j] = j - num;
						}
					}
				}
			}
		}
		printf("Case %d: %lld\n", ind, dp[cnt % 2][k]);
		// for(int i = 1; i <= n; i++) {
		// 	edges[i].clear();
		// }
		// int mov_j = k;
		// for(int i = cnt; i >= 1; mov_j = dp_from[i][mov_j], i--) {
		// 	if(parts[i].size() == 1) {
		// 		if(dp_from[i][mov_j] == mov_j) {
		// 			edges[parts[i][0].from].push_back(Edge{ parts[i][0].to, 1 });
		// 			edges[parts[i][0].to].push_back(Edge{ parts[i][0].from, 1 });
		// 		}
		// 	}
		// 	else {
		// 		int len = mov_j - dp_from[i][mov_j];
		// 		for(int j = (len != 0 ? len + 1 : 0); j < parts[i].size(); j++) {
		// 			edges[parts[i][j].from].push_back(Edge{ parts[i][j].to, 1 });
		// 			edges[parts[i][j].to].push_back(Edge{ parts[i][j].from, 1 });
		// 		}
		// 	}
		// }
		// memset(colors, 0, sizeof(fa)); // 'fa' is used for colors
		// int color_ind = 0;
		// for(int i = 1; i <= n; i++) {
		// 	if(!colors[i]) {
		// 		paint(i, ++color_ind);
		// 	}
		// 	// cout << colors[i] << ' ';
		// 	printf("%d ", colors[i]);
		// }
		// // cout << endl;
		// printf("\n");
	}
}


/*
2
8 9 4
5 1 1
1 6 2
6 8 3
6 7 4
7 8 5
1 2 6
2 3 7
3 4 8
2 4 9

5 6 10
1 2 1
1 3 2
2 3 3
1 4 4
1 5 5
4 5 6
*/
