#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 2e5 + 50;
constexpr int MOD = 1e9 + 7;
using ll = long long;
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

bool bits[50];

int main() {
	int T;
	cin >> T;
	while(T--) {
		memset(bits, 0, sizeof(bits));
		int n, m, l, r, num;
		cin >> n >> m;
		for(int i = 1; i <= m; i++) {
			cin >> l >> r >> num;
			for(int j = 0; j < 30; j++) {
				bits[j] |= (num >> j) & 1;
			}
		}
		int ans = 0;
		for(int i = 0; i < 30; i++) {
			if(bits[i]) {
				ans = add(ans, mul(pwr(2, n - 1), pwr(2, i)));
			}
		}
		cout << ans << endl;
	}
}