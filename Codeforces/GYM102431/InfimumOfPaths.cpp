#include <iostream>
#include <cstring>
#include <set>
using namespace std;
constexpr int MAXN = 2050;
constexpr int MAXM = 4050;
inline int min(int a, int b) {
	return a < b ? a : b;
}
using ll = long long;
constexpr ll MOD = 1e9 + 7;
inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll sub(ll a, ll b) {
	return add(a, MOD - b);
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
inline ll pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a), b >>= 1;
	}
	return res;
}
inline ll rev(ll a) {
	return pow(a, MOD - 2);
}
inline ll divi(ll a, ll b) {
	return mul(a, rev(b));
}

struct Edge {
	int to, val, nxt;
} edges[MAXM * 2];
int head[MAXN * 2];
void addEdge(int u, int v, int w, int i) {
	edges[i] = Edge{ v, w, head[u] };
	head[u] = i;
}

bool is_accessible[MAXN];

int n, m;
void dfs_from_1(int pos) {
	is_accessible[pos - n] = true;
	for(int i = head[pos]; i; i = edges[i].nxt) {
		int to = edges[i].to;
		if(!is_accessible[to - n]) {
			dfs_from_1(to);
		}
	}
}

int seq[MAXN * 2];
set <int> vertices[MAXN * 2];

int bfs_from_0() {
	vertices[0].insert(0);
	for(int i = 1; i <= 2 * n; i++) {
		int now_min_val = INT_MAX;
		for(auto pos: vertices[i - 1]) {
			int tmp_min_val = INT_MAX;
			for(int ei = head[pos]; ei; ei = edges[ei].nxt) {
				if(!is_accessible[edges[ei].to]) {
					continue;
				}
				tmp_min_val = min(tmp_min_val, edges[ei].val);
				if(edges[ei].val < now_min_val) {
					vertices[i].clear();
					now_min_val = tmp_min_val;
					vertices[i].insert(edges[ei].to);
				}
				else if(edges[ei].val == now_min_val) {
					vertices[i].insert(edges[ei].to);
				}
			}
		}
		seq[i] = now_min_val;
		if(vertices[i].count(1)) {
			return i;
		}
	}
	return 2 * n;
}

int nxt[MAXN], seq_cpy[MAXN];

void init() {
	memset(head, 0, sizeof(head));
	memset(edges, 0, sizeof(edges));
	memset(is_accessible, false, sizeof(is_accessible));

	memset(seq, 0x3f, sizeof(seq));
	for(int i = 0; i <= 2 * n; i++) {
		vertices[i].clear();
	}

	memset(nxt, -1, sizeof(nxt));
	memset(seq_cpy, 0x3f, sizeof(seq_cpy));
}

int main() {
	int T;
	cin >> T;
	for(int ind = 1; ind <= T; ind++) {
		init();
		cin >> n >> m;
		for(int i = 1; i <= m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			addEdge(u, v, w, i);
			addEdge(v + n, u + n, w, i + m);
		}
		dfs_from_1(1 + n);
		int len = bfs_from_0();
		ll ans = 0;
		if(len <= n) {
			for(int i = len; i >= 1; i--) {
				ans = divi(add(ans, seq[i]), 10);
			}
		}
		else {			
			// using kmp to solve out the circular section
			for(int i = 0; i <= n; i++) {
				seq_cpy[i] = seq[i + n];
			}
			int p = 0, k = -1;
			while(p <= n) {
				if(k == -1 || seq_cpy[p] == seq_cpy[k]) {
					++k, ++p;
					nxt[p] = k;
				}
				else {
					k = nxt[k];
				}
			}
			ll cir = 0;
			for(int i = n; i <= 2 * n - nxt[n + 1]; i++) {
				cir = add(mul(cir, 10), seq[i]);
			}
			ll tmp_ans = mul(divi(cir, pow(10ll, (long long)(2 * n - nxt[n + 1]))), 
							divi(1, sub(1, divi(1, pow(10ll, (long long)(n - nxt[n + 1] + 1))))));
			for(int i = n - 1; i >= 1; i--) {
				ans = divi(add(ans, seq[i]), 10);
			}
			ans = add(ans, tmp_ans);
		}
		printf("Case #%d: %lld\n", ind, ans);
	}
}