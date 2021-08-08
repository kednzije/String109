#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 100;
constexpr int MAXM = 200;
using ll = long long;
inline ll max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

ll dp[MAXN][MAXN][MAXM], a[MAXN];

int main() {
	memset(dp, 0x3f, sizeof(dp));
	int n, m = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		dp[i][i][a[i] / 2] = a[i];
		m = max(m, a[i]);
	}

	for(int len = 2; len <= n; len++) {
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			for(int k = 0; k <= m; k++) {
				dp[l][r][max(k, a[r]) / 2] = min(dp[l][r][max(k, a[r]) / 2], dp[l][r - 1][k] + max(0, a[r] - k));
			}
			for(int k = 0; k <= m; k++) {
				for(int p = l; p < r; p++) {
					for(int k1 = 0; k1 <= k; k1++) {
						dp[l][r][k] = min(dp[l][r][k], dp[l][p][k1] + dp[p + 1][r][k - k1]);
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		ll ans = INT_MAX;
		for(int k = 0; k <= m; k++) {
			ans = min(ans, dp[1][i][k]);
		}
		cout << ans << ' ';
	}
}