#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e3 + 10;
int to[4][2] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0
};

int n, m, nums[MAXN][MAXN];
bool vis[MAXN][MAXN];
vector <int> ans;

int dfs(int x, int y) {
	int sum = 1;
	vis[x][y] = true;
	for(int i = 0; i < 4; i++) {
		int to_x = x + to[i][0], to_y = y + to[i][1];
		if(!((nums[x][y] >> i) & 1) && !vis[to_x][to_y]) {
			sum += dfs(to_x, to_y);
		}
	}
	return sum;
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> nums[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(!vis[i][j]) {
				ans.push_back(dfs(i, j));
			}
		}
	}
	sort(ans.rbegin(), ans.rend());
	for(auto &size: ans) {
		cout << size << ' ';
	}
}