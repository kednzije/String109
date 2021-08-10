#include <iostream>
#include <assert.h>
using namespace std;
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

ll x[2], y[2];
inline ll sum_n2(ll n) {
	return divi(mul(n, mul(n + 1, add(mul(2, n), 1))), 6);
}
inline ll sum_a2_b2(ll a, ll b) {
	if(a > b) {
		return 0;
	}
	return sub(sum_n2(b), sum_n2(a - 1));
}
inline ll calc() {
	ll ans = sub(mul(pow(x[1], 2), pow(y[1], 2)), add(mul(pow(x[0], 2), pow(y[0], 2)), add(pow(x[1], 2), pow(y[1], 2))));
	if(x[0] > x[1]) {
		swap(x[0], x[1]), swap(y[0], y[1]);
	}
	if(y[0] <= y[1]) {
		bool upon_line[2];
		for(int i = 0; i < 2; i++) {
			upon_line[i] = (y[i] > x[i]);
		}
		if(upon_line[0] ^ upon_line[1]) {
			if(upon_line[0]) {
				// x ^ 2
				ans = add(ans, sum_a2_b2(x[0], x[1]));
				ans = add(ans, sum_a2_b2(y[0], y[1] - 1));
				// y ^ 2
				ans = add(ans, sum_a2_b2(y[0], y[1]));
				ans = add(ans, sum_a2_b2(y[0] + 1, y[1]));
				ans = add(ans, mul(y[0] - x[0], pow(y[0], 2)));
				ans = add(ans, mul(x[1] - y[1], pow(y[1], 2)));
			}
			else {
				// y ^ 2
				ans = add(ans, sum_a2_b2(y[0], y[1]));
				ans = add(ans, sum_a2_b2(x[0], x[1] - 1));
				// x ^ 2
				ans = add(ans, sum_a2_b2(x[0], x[1]));
				ans = add(ans, sum_a2_b2(x[0] + 1, x[1]));
				ans = add(ans, mul(x[0] - y[0], pow(x[0], 2)));
				ans = add(ans, mul(y[1] - x[1], pow(x[1], 2)));
			}
		}
		else {
			ans = add(ans, add(sum_a2_b2(x[0], x[1]), mul(y[1] - y[0], pow(x[upon_line[0]], 2))));
			ans = add(ans, add(sum_a2_b2(y[0], y[1]), mul(x[1] - x[0], pow(y[!upon_line[0]], 2))));
		}
	}
	else {
		ans = add(ans, add(sum_a2_b2(x[0], x[1]), mul(y[0] - y[1], pow(x[0], 2))));
		ans = add(ans, add(sum_a2_b2(y[1], y[0]), mul(x[1] - x[0], pow(y[1], 2))));
	}
	return ans;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> x[0] >> y[0] >> x[1] >> y[1];
		cout << calc() << endl;
	}
}