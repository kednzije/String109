#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
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
	while(b != 0) {
		if(b & 1) {
			res = mul(a, res);
		}
		a = mul(a, a), b >>= 1;
	}
	return res;
}

int main() {
	ll a, b, c, p, q, n;
	cin >> a >> b >> c >> p >> q >> n;
	ll sum_j_q = 0, last_max_j = 0, ans = 0;
	for(ll i = 0; i <= n; i++) {
		while((a * i + b) / c > last_max_j) {
			last_max_j++;
			sum_j_q = add(sum_j_q, pow(last_max_j, q));
		}
		ans = add(ans, mul(pow(i, p), sum_j_q));
	}
	cout << ans << endl;
}