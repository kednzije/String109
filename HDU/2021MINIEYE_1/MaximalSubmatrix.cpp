#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 2e3 + 5;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}

int n, m, mat[MAXN][MAXN], bound[MAXN][MAXN];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d", &mat[i][j]);
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(i == 1 || mat[i - 1][j] > mat[i][j]) {
					bound[i][j] = i;
				}
				else {
					bound[i][j] = bound[i - 1][j];
				}
			}
		}
		int ans = m;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				int height = i - bound[i][j] + 1;
				for(int k = j; k >= 1; k--) {
					height = min(height, i - bound[i][k] + 1);
					if(height == 1) {
						break;
					}
					ans = max(ans, height * (j - k + 1));
				}
			}
		}
		printf("%d\n", ans);
	}
}

/*
1
5 5
1 1 3 2 5
2 3 2 3 6
4 5 4 6 7
5 6 5 7 1
2 6 6 6 8

1
6 6
7 4 2 1 4 3
9 1 5 5 5 2
3 4 5 1 4 5
9 4 3 2 2 9
7 8 8 6 9 7
4 7 4 2 5 8
*/