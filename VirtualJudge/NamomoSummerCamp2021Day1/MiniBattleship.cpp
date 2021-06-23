#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
constexpr int MAXN = 10;
constexpr int dir[2][2] = {
	0, 1,
	1, 0,
};

char grid[MAXN][MAXN];
int n, k, sz[MAXN], clr[MAXN][MAXN], ans=0;

bool check() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(grid[i][j] == 'O' && clr[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}
inline bool pos_bad(int x, int y) {
	return x < 1 || x > n || y < 1 || y > n || grid[x][y] == 'X' || clr[x][y] != 0;
}

void dfs(int ind) {
	if(ind > k) {
		ans += check();
		return;
	}

	int pos_x, pos_y;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(pos_bad(i, j)) {
				continue;
			}
			for(int _dir = 0; _dir < 2; _dir++) {
				bool is_good = true;
				for(int k = 0; k < sz[ind]; k++) {
					pos_x = i + k * dir[_dir][0], pos_y = j + k * dir[_dir][1];
					if(pos_bad(pos_x, pos_y)) {
						is_good = false;
						break;
					}
				}
				if(is_good) {
					for(int k = 0; k < sz[ind]; k++) {
						pos_x = i + k * dir[_dir][0], pos_y = j + k * dir[_dir][1];
						clr[pos_x][pos_y] = ind;
					}
					dfs(ind + 1);
					for(int k = 0; k < sz[ind]; k++) {
						pos_x = i + k * dir[_dir][0], pos_y = j + k * dir[_dir][1];
						clr[pos_x][pos_y] = 0;
					}
				}

				if(sz[ind] == 1) {
					break;
				}
			}
		}
	}
}

int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> grid[i] + 1;
	}
	for(int i = 1; i <= k; i++) {
		cin >> sz[i];
	}
	dfs(1);
	cout << ans << endl;
}