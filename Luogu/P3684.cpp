#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;
constexpr int MAXN = 1e3 + 10;
constexpr int TO[8][2] = {
	1, 1,
	1, 0,
	1, -1,
	0, -1,
	-1, -1,
	-1, 0,
	-1, 1,
	0, 1
};
using StepLog = pair <int, pair <int, int>>;

struct Grid {
	char c_grid;
	int i_maxlen;
	int i_whichpart;
} grids[MAXN][MAXN];

int n;
char input_line[MAXN];
queue <StepLog> que;

int f[MAXN * MAXN];
int getf(int k) {
	if(k != f[k]) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
void merge(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if(fa == fb) {
		return;
	}
	if(rand() % 2) {
		f[fa] = fb;
	}
	else {
		f[fb] = fa;
	}
}

int main() {
	srand(time(NULL));
	memset(grids, 0, sizeof(grids));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", input_line + 1);
		for(int j = 1; j <= n; j++) {
			grids[i][j].c_grid = input_line[j];
			if(input_line[j] == '#') {
				que.push({ 0, { i, j } });
			}
			grids[i][j].i_maxlen = -1;
			grids[i][j].i_whichpart = -1;
		}
	}
	for(int i = 1; i <= n; i++) {
		// que.push({ 0, { 0, i } });
		// que.push({ 0, { n + 1, i } });
		// que.push({ 0, { i, 0 } });
		// que.push({ 0, { i, n + 1 } });
		que.push({ 1, { 1, i } });
		que.push({ 1, { n, i } });
		que.push({ 1, { i, 1 } });
		que.push({ 1, { i, n } });
	}
	// Calc the maxLen
	while(!que.empty()) {
		StepLog step = que.front();
		que.pop();
		int x_here = step.second.first, y_here = step.second.second, step_here = step.first;
		if(grids[x_here][y_here].i_maxlen != -1) {
			continue;
		}
		grids[x_here][y_here].i_maxlen = step_here;
		for(int i = 0; i < 8; i++) {
			int x = x_here + TO[i][0], y = y_here + TO[i][1];
			if(x < 1 || x > n || y < 1 || y > n || grids[x][y].c_grid != '.' || grids[x][y].i_maxlen != -1) {
				continue;
			}
			que.push({ step_here + 1, { x, y } });
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			grids[i][j].i_maxlen = grids[i][j].i_maxlen * 2 - 1;
		}
	}
	// Merge all adjacent grid with same maxLen
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(grids[i][j].c_grid != '.')
			for(int k = 1; k < 8; k += 2) {
				int x = i + TO[k][0], y = j + TO[k][1];
				if(grids[x][y].c_grid != '.' || grids[i][j].i_maxlen != grids[x][y].i_maxlen) {
					continue;
				}
				merge((i - 1) * n + j, (x - 1) * n + y);
			}
		}
	}
	// Add edges to the adjacent blocks
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			
		}
	}
}

/*
3
...
.#.
...
*/
