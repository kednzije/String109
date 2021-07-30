#include <iostream>
using namespace std;
constexpr int MAXN = 1e3;
inline int max(int a, int b) {
	return a > b ? a : b;
}

int n, m, weight[MAXN], value[MAXN], dp[MAXN][MAXN];

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> weight[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> value[i];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			dp[i][j] = dp[i - 1][j];
			if(weight[i] <= j) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - weight[i]] + value[i]);
			}
		}
	}
	cout << "Total Value: " << dp[n][m] << endl;
	while(n && m) {
		if(weight[n] <= m && dp[n - 1][m - weight[n]] + value[n] > dp[n - 1][m]) {
			cout << "Object No." << n
				<< ": weight " << weight[n]
				<< ", value " << value[n] << endl;
			m -= weight[n], n--;
			continue;
		}
		n--;
	}
}
/*
Input:
7 150
35 30 60 50 40 10 25
10 40 30 50 35 40 30
Output:

*/