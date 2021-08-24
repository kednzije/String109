#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 450;
constexpr int MAXK = 1e8 + 10;
using ll = long long;

ll n, k, p;
int sum[MAXN][2], fact[MAXK], pwr[MAXN][MAXN], ipwr[MAXN][MAXN];

// f(i, j): length is 'i', numbers ranges in [1, j]
ll f[MAXN][MAXN];

// g(i):	length is 'n', numbers ranges in [1, j] but each number in this range shoule show up at least once.
ll g[MAXN];

inline ll add(ll a, ll b) {
	return ((a % p) + (b % p)) % p;
}
inline ll sub(ll a, ll b) {
	return add(a, p - b);
}
inline ll mul(ll a, ll b) {
	return ((a % p) * (b % p)) % p;
}
inline ll pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) { 
			res = mul(res, a);
		}
		a = mul(a, a), b >>= 1;
	}
	return res;
}
inline ll divi(ll a, ll b) {
	return mul(a, pow(b, p - 2));
}
inline ll comb(ll a, ll b) {
	// C(a, b) : a <= b
	if(a > b) {
		return 0;
	}
	return divi(fact[b], mul(fact[a], fact[b - a]));
}

inline void init() {
	fact[0] = 1;
	for(int i = 1; i <= k; i++) {
		fact[i] = mul(fact[i - 1], i);
	}
	for(int i = 0; i <= n; i++) {
		pwr[i][0] = 1, pwr[i][1] = mul(1, i);
		ipwr[i][0] = 1, ipwr[i][1] = pow((ll)i, p - 2);
		
		for(int j = 2; j <= n; j++) {
			pwr[i][j] = mul(pwr[i][j - 1], i);
			// if(j > 1) {
			// 	ipwr[i][j] = mul(ipwr[i][j - 1], ipwr[i][1]);
			// }
			// ipwr[i][j] = pow(pwr[i][j], p - 2);
			ipwr[i][j] = mul(ipwr[i][j - 1], ipwr[i][1]);
		}
	}
}

int main() {
	cin >> n >> k >> p;
	init();
	// for(int i = 1; i <= n; i++) {
	// 	for(int j = 1; j <= n; j++) {
	// 		dp[i][j] = pow(j, i);
	// 		// for(int x = 1; x < i; x++) {
	// 		// 	for(int y = 1; y <= j; y++) {
	// 		// 		dp[i][j] = sub(dp[i][j], mul(sub(dp[i - x][j - y + 1], dp[i - x][j - y]), sub(pow(y, x), pow(y - 1, x))));
	// 		// 	}
	// 		// }
	// 	}
	// }
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(pow(i, j) != pwr[i][j]) {
				cout << i << ' ' << j << endl;
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(divi(1, pow(i, j)) != ipwr[i][j]) {
				cout << i << ' ' << j << endl;
			}
		}
	}
	for(int j = 1; j <= n; j++) {
		memset(sum, 0, sizeof(sum));
		for(int i = 1; i <= n; i++) {
			f[i][j] = pow(j, i);
			for(int y = 1; y <= j; y++) {
				// f[i][j] = sub(f[i][j], mul(pow(y, i), sum[y][0]));
				f[i][j] = sub(f[i][j], mul(pwr[y][i], sum[y][0]));
				// f[i][j] = add(f[i][j], mul(pow(y - 1, i), sum[y][1]));
				f[i][j] = add(f[i][j], mul(pwr[y - 1][i], sum[y][1]));
			}
			for(int y = 1; y <= j; y++) {
				// sum[y][0] = add(sum[y][0], divi(sub(f[i][j - y + 1], f[i][j - y]), pow(y, i)));
				sum[y][0] = add(sum[y][0], mul(sub(f[i][j - y + 1], f[i][j - y]), ipwr[y][i]));
				// sum[y][1] = add(sum[y][1], divi(sub(f[i][j - y + 1], f[i][j - y]), pow(y - 1, i)));
				sum[y][1] = add(sum[y][1], mul(sub(f[i][j - y + 1], f[i][j - y]), ipwr[y - 1][i]));
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		g[i] = f[n][i];
		for(int j = 1; j < i; j++) {
			g[i] = sub(g[i], mul(g[j], comb(j, i)));
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = add(ans, mul(g[i], comb(i, k)));
	}
	cout << ans << endl;
}