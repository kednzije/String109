#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 105;

int n, m;
bool edge[MAXN][MAXN], vis[MAXN];

void dfs(int pos) {
	vis[pos] = true;
	for(int i = 1; i <= n; i++) {
		if(vis[i] || !edge[pos][i]) {
			continue;
		}
		dfs(i);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x][y] = edge[y][x] = true;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(vis[i]) {
			continue;
		}
		cnt++;
		dfs(i);
	}
	for(int i = 1; i <= n; i++) {
		bool isolated = true;
		for(int j = 1; j <= n; j++) {
			if(edge[i][j]) {
				cnt--;
			}
		}
	}
	if(cnt % 1) {
		printf("Alice\n");
	}
	else {
		printf("Bob\n");
	}
}