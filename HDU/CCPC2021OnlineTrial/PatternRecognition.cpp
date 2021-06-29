#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <utility>
using namespace std;
constexpr int MAXN = 1e5 + 10;
constexpr int to[4][2] = {
	1, 0,
	0, 1,
	0, -1,
	-1, 0,
};

string img[MAXN], query;
int n, m, q, ans;
map <char, vector <pair <int, int>>> table;

void dfs(int i, bool hasTurned, int x, int y, int lastDir) {
	if(i == query.length()) {
		ans++;
		return;
	}
	int _x, _y;
	if(hasTurned) {
		_x = x + to[lastDir][0], _y = y + to[lastDir][1];
		if(_x < 0 || _x >= n || _y < 0 || _y >= m) {
			return;
		}
		if(img[_x][_y] == query[i]) {
			dfs(i + 1, hasTurned, _x, _y, lastDir);
		}
		return;
	}
	for(int dir = 0; dir < 4; dir++) {
		if(dir + lastDir == 3) {
			continue;
		}
		if(dir != lastDir && hasTurned) {
			continue;
		}
		_x = x + to[dir][0], _y = y + to[dir][1];
		if(_x < 0 || _x >= n || _y < 0 || _y >= m) {
			continue;
		}
		if(img[_x][_y] == query[i]) {
			dfs(i + 1, dir != lastDir, _x, _y, dir);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	scanf("%d", &t);

	while(t--) {
		table.clear();
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 0; i < n; i++) {
			cin >> img[i];
			for(int j = 0; j < m; j++) {
				table[img[i][j]].push_back(make_pair(i, j));
			}
		}
		while (q--) {
			ans = 0;
			cin >> query;
			vector <pair <int, int>> &vec = table[query[0]];
			if(query.length() == 1) {
				printf("%d\n", vec.size());
				continue;
			}
			else if(query.length() == 2) {
				for(int i = 0; i < vec.size(); i++) {
					for(int dir = 0; dir < 4; dir++) {
						int x = vec[i].first + to[dir][0], y = vec[i].second + to[dir][1];
						if(x < 0 || x >= n || y < 0 || y >= m) {
							continue;
						}
						ans += bool(img[x][y] == query[1]);
					}
				}
				if(query[0] == query[1]) {
					ans /= 2;
				}
				printf("%d\n", ans);
				continue;
			}
			for(int i = 0; i < vec.size(); i++) {
				int x = vec[i].first, y = vec[i].second;
				for(int dir = 0; dir < 4; dir++) {
					int _x = vec[i].first + to[dir][0], _y = vec[i].second + to[dir][1];
					if(_x < 0 || _x >= n || _y < 0 || _y >= m || img[_x][_y] != query[1]) {
						continue;
					}
					dfs(2, false, _x, _y, dir);
				}
			}
			bool isPalindrome = true;
			for(int i = 0; i < query.length(); i++) {
				if(query[i] != query[query.length() - 1 - i]) {
					isPalindrome = false;
					break;
				}
			}
			if(isPalindrome) {
				ans /= 2;
			}
			printf("%d\n", ans);
		}
	}
}
/*

2
10 10 1
xxxxxxxxxx
xbcdxxxxxx
xaxxxdcbax
xxxdxxxxxx
xxxcbaxxxx
xxxxxxabxx
xaxaxxdcxx
xbxbxxxxdc
xcxcxxxxxb
xdxdxxxxxa
abcd
5 5 2
xsssx
xxbxx
xbabx
xxbxx
xxxxx
bab
sss

*/