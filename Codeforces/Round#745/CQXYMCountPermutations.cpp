#include <iostream>
using namespace std;
typedef long long ll;
constexpr ll MAXN = 2e5 + 10;
constexpr ll MOD = 1e9 + 7;
inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
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
inline ll rev(ll a) {
	return pow(a, MOD - 2);
}
inline ll divi(ll a, ll b) {
	return mul(a, rev(b));
}

ll fac[MAXN];
void makeFac(ll n) {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
}

int main() {
	makeFac(2e5);
	int t;
	cin >> t;
	while(t--) {
		ll n;
		cin >> n;
		cout << divi(fac[n * 2], 2) << endl;
	}
}