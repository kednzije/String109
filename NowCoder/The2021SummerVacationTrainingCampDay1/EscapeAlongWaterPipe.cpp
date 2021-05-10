#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
constexpr int MAXN = 1005;

int n, m, stepCnt, endDir, pipes[MAXN][MAXN];
bool vis[MAXN][MAXN][4];

int to[4][2] = {
	0, 1,  // Right
	1, 0,  // Down
	0, -1, // Left
	-1, 0, // Up
};
int mapping[4][4] = {
	4, 3, -1, 0,
	1, 5, 0, -1,
	-1, 2, 4, 1,
	2, -1, 3, 5,
};

void printStep(int nextDir, int x, int y) {
	stepCnt++;
	if(x == 1 && y == 1) {
		int degree = 0;
		switch (pipes[1][1])
		{
		case 0: case 1: case 2: case 3:
			degree = ((6 - pipes[1][1]) % 4) * 90;
			break;
		case 4: case 5:
			degree = (nextDir + 4 != pipes[1][1]) * 90;
			break;
		
		default:
			break;
		}
		if(degree) {
			stepCnt++;
		}
		cout << stepCnt << endl;
		if(degree) {
			cout << "1 " << degree << " 1 1" << endl;
		}
		cout << "0 1 1" << endl;
		return;
	}
	
	int degree = 0;
	int fromDir = -1;
	if(x == n && y == m) {
		fromDir = endDir;
	}
	else {
		for(int i = 0; i < 4; i++) {
			if(vis[x][y][i]) {
				if(pipes[x][y] < 4 && (fromDir + nextDir) % 2) {
					fromDir = i;
					break;
				}
				if(pipes[x][y] >= 4 && fromDir == nextDir) {
					fromDir = i;
					break;
				}
			}
		}
	}
	if(pipes[x][y] < 4) {
		degree = (mapping[fromDir][nextDir] - pipes[x][y] + 4) % 4 * 90;
	}
	else {
		degree = (mapping[fromDir][nextDir] != pipes[x][y]) * 90;
	}
	if(degree) {
		stepCnt++;
	}
	printStep(fromDir, x - to[fromDir][0], y - to[fromDir][1]);

	if(degree) {
		cout << "1 " << degree << ' ' << x << ' ' << y << endl;
	}
	cout << "0 " << x << ' ' << y << endl;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(pipes, -1, sizeof(pipes));
		memset(vis, false, sizeof(vis));
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cin >> pipes[i][j];
			}
		}
		queue <pair <int, pair <int, int>>> que;
		vis[1][1][1] = true;
		que.push({1, {1, 1}});
		endDir = -1;
		while(!que.empty()) {
			pair <int, pair <int, int>> pos = que.front();
			int x0 = pos.second.first, 
				y0 = pos.second.second;
			que.pop();
			if(x0 == n && y0 == m) {
				switch (pipes[n][m])
				{
				case 0: case 1: case 2: case 3:
					if(pos.first == 0) {
						endDir = 0;
					}
					break;
				case 4: case 5:
					if(pos.first == 1) {
						endDir = 1;
					}
					break;
				default:
					break;
				}
				if(endDir != -1) {
					break;
				}
			}
			for(int i = 0; i < 4; i++) {
				int x = x0 + to[i][0], 
					y = y0 + to[i][1];
				if(pipes[x][y] == -1 || vis[x][y][i]) {
					continue;
				}
				if(pipes[x0][y0] < 4 && (pos.first + i) % 2) {
					vis[x][y][i] = true;
					que.push({i, {x, y}});
				}
				if(pipes[x0][y0] >= 4 && pos.first == i) {
					vis[x][y][i] = true;
					que.push({i, {x, y}});
				}
			}
		}
		if(endDir != -1) {
			cout << "YES" << endl;
			stepCnt = 0;
			printStep(1, n, m);
		}
		else {
			cout << "NO" << endl;
		}
	}
}