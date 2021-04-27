#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
const int MAXVER = 4e5 + 5;

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

int n, m, paths[MAXVER];
bool vis[MAXVER];
void init() {
	memset(firstEdge, 0, sizeof(firstEdge));

	memset(paths, 0, sizeof(paths));
	memset(vis, false, sizeof(vis));
}

void dfs(int pos, bool infinite) {
	vis[pos] = true;
	paths[pos] = infinite ? -1 : (paths[pos] == 0 ? 1 : 2);
	for(int i = firstEdge[pos]; i; i = edgeData[i].next) {
		int to = edgeData[i].to;
		if((infinite || vis[to]) && paths[to] != -1) {
			dfs(to, true);
		}
		else if(!vis[to] && paths[to] == 1) {
			dfs(to, infinite);
		}
		else if(paths[to] == 0) {
			dfs(to, infinite);
		}
	}
	vis[pos] = false;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		init();
		for(int i = 1; i <= m; i++) {
			int from, to;
			scanf("%d%d", &from, &to);
			addEdge(i, from, to);
		}
		dfs(1, false);
		for(int i = 1; i <= n; i++) {
			printf("%d ", paths[i]);
		}
		printf("\n");
	}
}
/*
1
10 9
1 2
1 6
3 4
5 6
3 3
6 8
8 2
6 4
2 3
*/