/**
 * @file CactusFindCircle.cpp
 * @author From Web
 * @brief Used to find all circles in a cactus graph
 * @version 0.1
 * @date 2021-11-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// if also need to get single vertice
// #define NEED_SINGLE_VERTICE

#include <vector>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int n, cnt, depth[MAXN], fa[MAXN];
struct Edge {
	int to, val;
};
vector <Edge> edges[MAXN];
vector <int> vertices[MAXN];
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
	vertices[cnt].push_back(y);
#ifdef NEED_SINGLE_VERTICE
	in_a_circle[y] = true;
#endif
	for (; x != y; x = fa[x]) {
		vertices[cnt].push_back(x);
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

// Test
#include <iostream>

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[u].push_back(Edge{ v, w }), edges[v].push_back(Edge{ u, w });
	}
	dfs(1, 0);
	for(int i = 1; i <= cnt; i++) {
		for(auto ver: vertices[i]) {
			cout << ver << ' ';
		}
		cout << endl;
	}
}

/*
Input:
8 9
5 1 1
1 6 1
6 8 1
6 7 1
7 8 1
1 2 1
2 3 1
3 4 1
2 4 1
Output: // Define NEED_SINGLE_VERTICE
5 
6 7 8
2 4 3
1

Input:
5 6
1 2 1
1 3 1
2 3 1
1 4 1
1 5 1
4 5 1
Output:
1 3 2 
1 5 4
*/