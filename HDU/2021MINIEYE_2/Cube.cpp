#include <iostream>
#include <cstdio>
using namespace std;
constexpr int mod = 1e9 + 7;
typedef long long ll;
inline ll add(ll a, ll b) {
	return ((a % mod) + (b % mod) + mod) % mod;
}
inline ll mul(ll a, ll b) {
	return ((a % mod) * (b % mod)) % mod;
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
	return mul(a, pow(b, mod - 2));
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		ll n;
		scanf("%lld", &n);
		ll ans = mul(2, pow(mul(n, n - 1), 2));
		printf("%lld\n", ans);
	}
}