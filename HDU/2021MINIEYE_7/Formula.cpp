#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e5 + 5;
using ll = long long;
constexpr ll MOD = 998244353;
inline ll add(ll a, ll b) {
	return (a % MOD + b % MOD) % MOD;
}
inline ll mul(ll a, ll b) {
	return (a % MOD * b % MOD) % MOD;
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
	return mul(a, pow(b, MOD - 2));
}

ll fac[MAXN];

void mk_fac() {
	fac[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
}

ll comb(ll n, ll m) {
	if(m > n) {
		return 0;
	}
	return divi(divi(fac[n], fac[n - m]), fac[m]);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		
	}
}