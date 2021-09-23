#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e2 + 10;
constexpr int TO[4][2] = {
	1, 0,
	0, 1,
	0, -1,
	-1, 0
};

int grids[MAXN][MAXN];

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> grids[i][j];
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			for(int k = 0; k < 4; k++) {
				ans += (grids[i][j] == 1 && grids[i + TO[k][0]][j + TO[k][1]] == 0);
			}
		}
	}
	cout << ans << endl;
	return 0;
}