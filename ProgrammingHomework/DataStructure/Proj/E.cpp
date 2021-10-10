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
constexpr ll INF = 9223372036854775807ll;

struct Edge {
	int to, nxt;
	ll dis, cost, line; // val[0] is dis, val[1] is cost.
} edges[MAXN * MAXN * 4];
int head[MAXN], pre_edge[MAXN * MAXN * 4];
int add_edge(int u, int v, ll w) { // return the index of edge
	edges[++edges[0].dis] = { v, head[u], w, 0, 0 };
	head[u] = edges[0].dis;
	return edges[0].dis;
}

ll path[MAXN], switch_cost[MAXN], path_len[MAXN];
ll ans = INF, min_tmp_ans[MAXN];

void dfs(const int src, const int dst, ll dis, ll cost, int pre_edge_ind) {
	if(src == dst) {
		ans = get_min(ans, dis * cost);
		return;
	}
	if(dis * cost >= ans) {
		return;
	}
	if(dis * cost > min_tmp_ans[src]) {
		return;
	}
	min_tmp_ans[src] = get_min(min_tmp_ans[src], dis * cost);
	
	for(int i = head[src]; i; i = edges[i].nxt) {
		int to = edges[i].to, to_line = edges[i].line;
		dfs(
			to, 
			dst, 
			dis + edges[i].dis + ((edges[pre_edge_ind].line != to_line || /* if equal */ pre_edge_ind != pre_edge[i]) ? switch_cost[to_line] : 0), 
			cost + edges[i].cost, 
			i
		);
	}
}

int main() {
	int n, m, src, dst;
	n = input(), m = input(), src = input(), dst = input();

	for(int i = 1; i <= m; i++) {
		path_len[i] = input();
	}
	for(int i = 1; i <= m; i++) {
		switch_cost[i] = input();
	}

	for(int k = 1; k <= m; k++) {
		ll len = path_len[k], dis;
		for(int j = 1; j <= len; j++) {
			path[j] = input();
		}
		for(int j = 1; j < len; j++) {
			dis = input();
			path[j] = add_edge(path[j], path[j + 1], dis);
		}
		for(int j = 1; j < len; j++) {
			edges[path[j]].cost = input();
			edges[path[j]].line = k;
			pre_edge[path[j]] = path[j - 1];
		}
	}

	for(int i = 1; i <= n; i++) {
		min_tmp_ans[i] = INF;
	}
	dfs(src, dst, 0, 0, 0);
	printf("%lld\n", ans);
	return 0;
}