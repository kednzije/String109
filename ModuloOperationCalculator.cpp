#include <iostream>
using namespace std;
typedef long long ll;
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

int main() {
	ll a, b;
	cin >> a >> b;
	cout << dvd(a, b) << endl;
}