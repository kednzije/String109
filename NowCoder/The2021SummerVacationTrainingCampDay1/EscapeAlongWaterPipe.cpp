#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
constexpr int MAXN = 1005;

int n, m, endDir, pipes[MAXN][MAXN];
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

void printStep() {
	int nextDir = 1, x = n, y = m;
	vector <vector <int>> steps;
	while(true) {
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
			steps.push_back({0, 1, 1});
			if(degree) {
				steps.push_back({1, degree, 1, 1});
			}
			break;
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

		steps.push_back({0, x, y});

		if(degree) {
			steps.push_back({1, degree, x, y});
		}

		x -= to[fromDir][0], y -= to[fromDir][1], nextDir = fromDir;
	}

	cout << steps.size() << endl;
	for(int i = steps.size() - 1; i >= 0; i--) {
		for(int j = 0; j < steps[i].size(); j++) {
			cout << steps[i][j] << ' ';
		}
		cout << endl;
	}
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
			auto pos = que.front();
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
			printStep();
		}
		else {
			cout << "NO" << endl;
		}
	}
}