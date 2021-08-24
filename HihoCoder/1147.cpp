#include <iostream>
#include <map>
#include <utility>
using namespace std;
constexpr int MAXN = 150;

using ll = long long;
constexpr ll MOD = 1e9 + 7;

inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll sub(ll a, ll b) {
	return add(a, MOD - b);
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
map <pair <ll, ll>, ll> pwr;
inline ll pow(ll a, ll b) {
	if(pwr.count({ a, b })) {
		return pwr[{ a, b }];
	}
	ll res = 1;
	while(b) {
		if(b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a), b >>= 1;
	}
	pwr[{ a, b }] = res;
	return res;
}
inline ll divi(ll a, ll b) {
	return mul(a, pow(b, MOD - 2));
}
map <ll, ll> fct;
inline ll fact(ll k) {
	if(k == 0 || k == 1) {
		return 1ll;
	}
	if(fct.count(k)) {
		return fct[k];
	}
	fct[k] = mul(k, fact(k - 1));
	return fct[k];
}
inline ll comb(ll a, ll b) {
	// a <= b
	if(a > b) {
		return 0;
	}
	return divi(fact(b), mul(fact(a), fact(b - a)));
}

ll n, m, dp[MAXN][MAXN][MAXN];

int main() {
	cin >> n >> m;
	dp[1][1][1] = 1; // node 1
	for(int i = 2; i <= m + 1; i++) { // already make (i - 1) layers
		for(int j = i; j <= n; j++) { // the total number of nodes is 'j'
			for(int k = 1; k <= j - (i - 1); k++) { // this layer has 'k' nodes
				dp[i][j][k] = 0;
				ll inside_edges_cnt_mul_comb = mul(pow(2ll, divi(mul(k, k - 1), 2ll)), comb(k, n - (j - k)));
				for(int p = 1; p <= (j - k) - (i - 2); p++) { // last layer has 'p' nodes
					dp[i][j][k] = add(dp[i][j][k], mul(dp[i - 1][j - k][p], mul(inside_edges_cnt_mul_comb, pow(sub(pow(2ll, (ll)p), 1ll), (ll)k))));
				}
			}
		}
	}
	ll ans = 0;
	for(int i = m; i <= n; i++) { // 1st ~ 'm'th layer have 'i' nodes
		for(int j = 1; j <= i - m + 1; j++) { // the 'm'th layer has 'j' nodes
			// so (m + 1)th layer has (n - i) nodes
			ans = add(ans, mul(dp[m + 1][i][j], mul(j, mul(pow(2ll, divi(mul(n - i, n - i - 1), 2ll)), pow(2, mul(j, n - i))))));
		}
	}
	cout << divi(ans, n - 1) << endl;
}