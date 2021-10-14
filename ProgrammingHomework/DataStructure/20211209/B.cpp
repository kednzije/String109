#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 2e3 + 50;

bool hate[MAXN][MAXN], vis[MAXN];

bool dfs1(int u, const int n, const int len) {
	vis[u] = true;
	for(int v = 1; v <= n; v++) {
		if(hate[u][v]) {
			if(vis[v]) {
				if(len % 2 == 0) {
					return false;
				}
			}
			else {
				dfs1(v, n, len + 1);
			}
		}
	}
	return true;
}
void dfs2(int u, const int n) {
	vis[u] = true;
	for(int v = 1; v <= n; v++) {
		if(!hate[u][v] && !vis[v]) {
			dfs2(v, n);
		}
	}
}

int main() {
	int n;
	cin >> n;
	memset(hate, true, sizeof(hate));
	int u, v;
	while(cin >> u >> v) {
		hate[u][v] = hate[v][u] = false;
	}
	bool good = true;
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			good &= dfs1(i, n, 0);
			if(!good) {
				break;
			}
		}
	}
	int cnt = 0;
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			cnt++;
			if(cnt > 2) {
				break;
			}
			dfs2(i, n);
		}
	}
	cout << (good && (cnt <= 2)) << endl;
}