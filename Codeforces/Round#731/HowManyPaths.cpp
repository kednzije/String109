// false

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
const int MAXVER = 4 * 1e5 + 5;

struct edge {
	int to, next;
	edge() {
		to = next = 0;
	}
	edge(int _to, int _next) {
		to = _to, next = _next;
	}
} edgeData[MAXVER];
int firstEdge[MAXVER];
void addEdge(int i, int from, int to) {
	edgeData[i] = edge(to, firstEdge[from]);
	firstEdge[from] = i;
}

int paths[MAXVER];

// find out the circle
int tim=0, top=0, low[MAXVER], dfn[MAXVER], sta[MAXVER];
bool vis[MAXVER];
void tag(int pos) {
	low[pos] = dfn[pos] = ++tim;
	sta[++top] = pos;
	vis[pos] = true;
	for(int i = firstEdge[pos]; i; i = edgeData[i].next) {
		int to = edgeData[i].to;

		if(!dfn[to]) {
			tag(to);
			low[pos] = min(low[pos], low[to]);
		}
		else if(vis[to]) {
			low[pos] = min(low[pos], low[to]);
		}

		if(pos == to) {
			paths[pos] = -1;
		}
	}

	if(dfn[pos] == low[pos]) {
		int ver;
		bool isInfinite = false;
		while(top) {
			ver = sta[top--];
			vis[ver] = false;
			if(pos == ver) {
				break;
			}
			isInfinite = true;
			paths[ver] = -1;
		}
		if(isInfinite) { paths[pos] = -1; }
	}
}

void dfs(int pos, int isInfinite) {
	vis[pos] = true;
	if(paths[pos] == -1) {
		isInfinite = true;
	}
	for(int i = firstEdge[pos]; i; i = edgeData[i].next) {
		int to = edgeData[i].to;
		if(vis[to]) {
			if(paths[to] != -1) { paths[to] = isInfinite ? -1 : 2; }
			continue;
		}
		if(paths[to] != -1) { paths[to] = isInfinite ? -1 : 1; }
		dfs(to, isInfinite);
	}
}

void init() {
	memset(firstEdge, 0, sizeof(firstEdge));
	memset(paths, 0, sizeof(firstEdge));

	tim = top = 0;
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(sta, 0, sizeof(sta));
	memset(vis, false, sizeof(vis));

	paths[1] = 1;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		// cin >> n >> m;
		scanf("%d%d", &n, &m);
		init();
		for(int i = 1; i <= m; i++) {
			int from, to;
			// cin >> from >> to;
			scanf("%d%d", &from, &to);
			addEdge(i, from, to);
		}
		tag(1);
		dfs(1, false);

		for(int i = 1; i <= n; i++) {
			// cout << paths[i] << ' ';
			printf("%d ", paths[i]);
		}
		// cout << endl;
		printf("\n");
	}
}