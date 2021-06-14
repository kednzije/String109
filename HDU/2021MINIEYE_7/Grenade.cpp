/*
	Author:Frozencode
*/
#include <iostream>
#include <cstdio>
#include <utility>
#include <cmath>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 500010;
const ll INF = 2147483647;
const ll MOD = 1e9 + 7;
const double pi = acos(-1.0);
ll t;
double v0, t0, r, phi, c;

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

int main()
{ 
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--){
		cin >> t0 >> v0 >> r;
		phi = (r * r - 25.0 * t0 * t0 * t0 * t0 - v0 * v0 * t0 * t0) / (10.0 * v0 * t0 * t0 * t0);
		if(phi <= -1.00000000000){
			cout << 1 << endl;
			continue;
		}
		else if(phi >= 1.00000000000){
			cout << 0 << endl;
			continue;
		}
		c = acos(phi);
		// printf("%.20f\n", phi);
		// printf("%.20f\n", c / pi);
		printf("%lld\n", divi((c / pi) * (MOD - 1), (MOD - 1)));
	}
	return 0;
}