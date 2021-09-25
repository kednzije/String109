#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
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

map <ll, ll> ans;

ll calc(ll n) {
	ll k = (n - 1) / 3;
	return mul(
		pwr(2, n - 1),
		add(
			mul(
				dvd(8, 3),
				sub(
					mul(
						add(
							dvd(k, 8),
							dvd(1, 9)
						),
						pwr(
							sub(
								0,
								dvd(1, 8)
							),
							k
						)
					),
					dvd(1, 9)
				)
			),
			mul(
				dvd(n, 9),
				sub(
					1,
					pwr(
						sub(
							0,
							dvd(1, 8)
						),
						k
					)
				)
			)
		)
	);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		ll n;
		scanf("%lld", &n);
		if(!ans.count(n)) {
			ans[n] = calc(n);
		}
		printf("%lld\n", ans[n]);
	}
}