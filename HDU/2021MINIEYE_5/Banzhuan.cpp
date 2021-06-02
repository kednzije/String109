/*
	Author:Frozencode
*/
#include <iostream>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 500010;
const ll INF = 2147483647;
const ll mod = 1e9 + 7;
ll t, n, minn, maxx;
ll sqr(ll x){return (x % mod) * x % mod;}
ll qpow(ll x, ll y){return y ? qpow(sqr(x), y / 2) * (y & 1 ? x : 1) % mod : 1;}
ll add(ll x, ll y){return (x + y) % mod;}
ll sub(ll x, ll y){return (x + mod - y) % mod;}
ll mul(ll x, ll y){return (x % mod) * y % mod;}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--){
		cin >> n;
		minn = maxx = 0;
		minn = add(minn, sqr(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)))); //y = 1 x-z
		//cout << sqr(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2))) << endl;
		minn = add(minn, mul(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)), mul(mul(mul(n % mod, add(n % mod, 1)), add(mul(n % mod, 2), 1)), qpow(6, mod - 2)))); //x = 1 y-z
		//cout << mul(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)), mul(mul(mul(n % mod, add(n, 1)), add(mul(n, 2), 1)), qpow(6, mod - 2))) << endl;
		minn = add(minn, mul(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)), mul(mul(mul(n % mod, add(n % mod, 1)), add(mul(n % mod, 2), 1)), qpow(6, mod - 2)))); //z = 1 y-x
		//cout << mul(mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)), mul(mul(mul(n % mod, add(n, 1)), add(mul(n, 2), 1)), qpow(6, mod - 2))) << endl;
		minn = sub(minn, mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2))); // x = y = 1 z
		//cout << mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)) << endl;
		minn = sub(minn, mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2))); // y = z = 1 x
		//cout << mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2)) << endl;
		minn = sub(minn, mul(mul(mul(n % mod, add(n, 1)), add(mul(n, 2), 1)), qpow(6, mod - 2))); // x = z = 1 y
		//cout << mul(mul(mul(n % mod, add(n, 1)), add(mul(n, 2), 1)), qpow(6, mod - 2)) << endl;
		minn = sub(minn, mul(mul(n % mod, (n + 1) % mod), qpow(2, mod - 2))); // x = y = 1 z
		minn = add(minn, 1);
		minn = add(minn, 1); // cube 1
		maxx = mul(sqr(mul(mul(n % mod, add(n, 1)), qpow(2, mod - 2))), mul(mul(mul(n % mod, add(n, 1)), add(mul(n, 2), 1)), qpow(6, mod - 2)));
		cout << minn << endl;
		cout << maxx << endl;
		//cout << minn << " " << maxx << endl;
	}
	return 0;
}