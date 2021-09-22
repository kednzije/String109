#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 50;
constexpr int MAXM = 1e5 + 50;
using ll = long long;

// int INPUT() {
//     int x=0,f=1;char ch=getchar();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//     return x*f;
// }

int head[MAXN], edge_cnt;
struct Edge {
	int to, val, nxt;
} edges[MAXM * 3];
void add_edge(int u, int v, int w) {
	edges[++edge_cnt] = { v, w, head[u] };
	head[u] = edge_cnt;
}

int n, m;
ll ans;

ll dis[MAXN], cnt[MAXN];
bool vis[MAXN];
bool run_SPFA(const int src) {
	memset(dis, 0, sizeof(dis));
	memset(vis, false, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	queue <int> que;
	que.push(src), vis[src] = true, dis[src] = 0;
	int u, v, w;
	while(!que.empty()) {
		u = que.front();
		que.pop();
		vis[u] = false;
		for(register int i = head[u]; i; i = edges[i].nxt) {
			v = edges[i].to, w = edges[i].val;
			if(dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if(!vis[v]) {
					if(++cnt[v] > n) {
						return false;
					}
					que.push(v), vis[v] = true;
				}
			}
		}
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	// n = INPUT(), m = INPUT();
	int k, x, y;
	for(register int i = 1; i <= m; i++) {
		// int k, x, y;
		scanf("%d%d%d", &k, &x, &y);
		// k = INPUT(), x = INPUT(), y = INPUT();
		switch (k) {
		case 1:
			add_edge(x, y, 0), add_edge(y, x, 0);
			break;
		case 2:
			add_edge(x, y, 1);
			if(x == y) {
				ans = -1;
				printf("%lld\n", ans);
				return 0;
			}
			break;
		case 3:
			add_edge(y, x, 0);
			break;
		case 4:
			add_edge(y, x, 1);
			if(x == y) {
				ans = -1;
				printf("%lld\n", ans);
				return 0;
			}
			break;
		case 5:
			add_edge(x, y, 0);
			break;
		
		default:
			break;
		}
	}
	for(register int i = n; i >= 1; i--) { // if use 1 ~ n, it will TLE. But random permutation will also TLE.
		add_edge(0, i, 1);
	}

	// for(int i = 1; i <= n; i++) {
	// 	cnt[i] = i;
	// }
	// random_shuffle(cnt + 1, cnt + 1 + n);
	// for(register int i = 1; i <= n; i++) {
	// 	add_edge(0, cnt[i], 1);
	// }

	if(!run_SPFA(0)) {
		ans = -1;
	}
	else {
		ans = 0;
		for(register int i = 1; i <= n; i++) {
			ans += dis[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
}

/*
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1

11
*/