#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 505;
using ll = long long;
constexpr ll MOD = 998244353;
inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll sub(ll a, ll b) {
	return add(a, MOD - b);
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
inline ll pwr(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a), b >>= 1;
	}
	return res;
}
inline ll rev(ll a) {
	return pwr(a, MOD - 2);
}
inline ll dvd(ll a, ll b) {
	return mul(a, rev(b));
}

ll fact[MAXN], fact_rev[MAXN], comb[MAXN][MAXN];
inline ll get_comb(ll n, ll m) {
	if(m > n) {
		return 0;
	}
	if(comb[n][m] == 0) {
		comb[n][m] = mul(fact[n], mul(fact_rev[n - m], fact_rev[m]));
	}
	return comb[n][m];
}

int F[MAXN][MAXN];
ll getF(ll n, ll x) {
	if(F[n][x] != 0) {
		return F[n][x];
	}
	if(n == 1) {
		return 0;
	}
	if(x == 1 || n == 0) {
		return 1;
	}
	if(x < n) {
		F[n][x] = pwr(x, n);
		return F[n][x];
	}
	ll ans = 0;
	for(int i = 0; i <= n; i++) {
		ans = add(ans, mul(get_comb(n, i), mul(pwr(n - 1, n - i), getF(i, x - n + 1))));
	}
	F[n][x] = ans;
	return ans;
}

int main() {
	fact[0] = 1, fact_rev[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fact[i] = mul(fact[i - 1], i);
		fact_rev[i] = mul(fact_rev[i - 1], rev(i));
	}
	int n, x;
	cin >> n >> x;
	cout << getF(n, x);
	return 0;
}