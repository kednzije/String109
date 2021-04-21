#include <iostream>
#include <cstring>
#include <set>
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

bool seen[MAXVER];
int paths[MAXVER];
set <int> sta;

void init() {
	memset(firstEdge, 0, sizeof(firstEdge));
	memset(seen, false, sizeof(seen));
	memset(paths, 0, sizeof(firstEdge));
	sta.clear();

	paths[1] = 1;
}

void dfs(int pos, bool isInfinite);

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		init();
		for(int i = 1; i <= m; i++) {
			int from, to;
			cin >> from >> to;
			addEdge(i, from, to);
		}
		dfs(1, false);

		for(int i = 1; i <= n; i++) {
			cout << paths[i] << ' ';
		}
		cout << endl;
	}
}

void dfs(int pos, bool isInfinite) {
	sta.insert(pos);
	seen[pos] = true;
	for(int i = firstEdge[pos]; i; i = edgeData[i].next) {
		int to = edgeData[i].to;
		if(sta.count(to)) {
			paths[to] = -1;
			isInfinite = true;
			continue;
		}
		if(seen[to]) {
			paths[to] = isInfinite ? -1 : 2;
			continue;
		}
		paths[to] = isInfinite ? -1 : 1;
		dfs(to, isInfinite);
	}
	sta.erase(pos);
}