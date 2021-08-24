#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
typedef long long ll;
const int maxn = 103;

int n, m, fac[maxn], facinv[maxn], mi[maxn];
ll dp[maxn][maxn][maxn], ans;

int qmi(ll a, ll b)
{
	int ret = 1;
	for (a %= MOD; b; b >>= 1, a = 1ll * a * a % MOD)
		if (b & 1)
			ret = 1ll * ret * a % MOD;
	return ret;
}
int C(int n, int m)
{
	if (n < m)
		return 0;
	return 1ll * fac[n] * facinv[n - m] % MOD * facinv[m] % MOD;
}
int main()
{
	scanf("%d%d", &n, &m);
	facinv[0] = facinv[1] = fac[0] = mi[0] = 1;
	for (int i = 2; i <= 100; i++)
		facinv[i] = MOD - 1ll * MOD / i * facinv[MOD % i] % MOD;
	for (int i = 1; i <= 100; i++)
		mi[i] = 2ll * mi[i - 1] % MOD, fac[i] = 1ll * fac[i - 1] * i % MOD, facinv[i] = 1ll * facinv[i - 1] * facinv[i] % MOD;
	dp[1][1][1] = 1;
	for (int i = 2; i <= m + 1; i++)
		for (int j = i; j <= n; j++)
			for (int k = 1; k <= j - i + 1; k++)
				for (int p = 1; p <= j - k - i + 2; p++)
					dp[i][j][k] = (dp[i][j][k] + 1ll * dp[i - 1][j - k][p] * qmi(mi[p] - 1, k) % MOD * C(n - j + k, k) % MOD * qmi(2, C(k, 2)) % MOD) % MOD;

	for(int i = 1; i <= m; i++) {
		cout << endl;
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k <= n; k++) {
				cout << i << "\t" << j << '\t' << k << ":\t" << dp[i][j][k] << endl;
			}
			cout << endl;
		}
	}
	
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		if (dp[k + 1][i][j])
	for(int i = m; i <= n; i++)
		for(int j = 1; j <= i - m + 1; j++)
				ans = (ans + 1ll * dp[m + 1][i][j] * j % MOD * qmi(2, C(n - i, 2)) % MOD * qmi(2, 1ll * j * (n - i) % MOD)) % MOD;
	printf("%lld\n", 1ll * ans * qmi(n - 1, MOD - 2) % MOD);
	return 0;
}