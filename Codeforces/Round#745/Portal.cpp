#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 500;

int sum[MAXN][MAXN];

int calc(int x1, int y1, int x2, int y2) {
	return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(sum, 0, sizeof(sum));
		int n, m;
		cin >> n >> m;
		string s;
		for(int i = 1; i <= n; i++) {
			cin >> s;
			for(int j = 0; j < m; j++) {
				sum[i][j + 1] = sum[i - 1][j + 1] + sum[i][j] - sum[i - 1][j] + (s[j] == '1');
			}
		}
		// for(int i = 1; i <= n; i++) {
		// 	for(int j = 1; j <= m; j++) {
		// 		cout << sum[i][j] << ' ';
		// 	}
		// 	cout << endl;
		// }
		int minans = INT_MAX;
		for(int i1 = 1; i1 <= n - 4; i1++) {
			for(int j1 = 1; j1 <= n - 3; j1++) {
				if(calc(i1 + 1, j1 + 1, i1 + 3, j1 + 2) > minans) {
					continue;
				}
				for(int i2 = i1 + 4; i2 <= n; i2++) {
					for(int j2 = j1 + 3; j2 <= m; j2++) {
						minans = min(minans, 
							2 * (i2 - i1 - 1) - calc(i1 + 1, j1, i2 - 1, j1) - calc(i1 + 1, j2, i2 - 1, j2) 
							+ 2 * (j2 - j1 - 1) - calc(i1, j1 + 1, i1, j2 - 1) - calc(i2, j1 + 1, i2, j2 - 1) 
							+ calc(i1 + 1, j1 + 1, i2 - 1, j2 - 1));
					}
				}
			}
		}
		cout << minans << endl;
	}
}