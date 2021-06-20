#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5 + 10;
using ll = long long;
inline int min(int a, int b) {
	return a < b ? a : b;
}
inline int max(int a, int b) {
	return a > b ? a : b;
}

int n, m, val[2][MAXN];
ll k;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%lld", &n, &m, &k);
		if(k == 1) {
			int row_max = -1;
			for(int j = 1; j <= m; j++) {
				scanf("%d", &val[1][j]);
				row_max = max(row_max, val[1][j]);
			}
			for(int i = 2; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					scanf("%d", &val[1][j]);
				}
			}
			printf("%d\n", row_max);
			continue;
		}
		int row_min = INT_MAX, col_max = -1, val_1_1;
		memset(val, 0, sizeof(val));
		for(int j = 1; j <= m; j++) {
			val[0][j] = INT_MAX;
		}
		for(int i = 1; i <= n; i++) {
			int row_max = -1;
			for(int j = 1; j <= m; j++) {
				scanf("%d", &val[1][j]);
				if(1 == i && 1 == j) {
					val_1_1 = val[1][j];
				}
				row_max = max(row_max, val[1][j]);
				val[0][j] = min(val[0][j], val[1][j]);

				if(i == n) {
					col_max = max(col_max, val[0][j]);
				}
			}
			row_min = min(row_min, row_max);
		}
		if(k % 2) {
			printf("%d\n", max(val_1_1, row_min));
		}
		else {
			printf("%d\n", max(val_1_1, col_max));
		}
	}
}