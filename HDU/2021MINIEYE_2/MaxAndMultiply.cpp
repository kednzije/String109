#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
constexpr int MAXN = (1 << 18 + 5);
constexpr long long mod = 998244353;
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
inline ll max(ll a, ll b) {
	return a > b ? a : b;
}

int n;
ll maxABs[MAXN], a[MAXN], b[MAXN];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		memset(maxABs, 0, sizeof(maxABs));
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
		}
		for(int i = 0; i < n; i++) {
			scanf("%lld", &b[i]);
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				maxABs[i & j] = max(maxABs[i & j], mul(a[i], b[i]));
			}
		}
		ll maxAB = 0, ans = 0;
		for(int i = n - 1; i >= 0; i--) {
			maxAB = max(maxABs[i], maxAB);
			ans = add(ans, maxAB);
		}
		printf("%lld\n", ans);
	}
}