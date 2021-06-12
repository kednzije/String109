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
const ll mod = 4933;
ll add(ll x, ll y){return (x + y) % mod;}
ll sub(ll x, ll y){return (x + mod - y) % mod;}
ll mul(ll x, ll y){return x * y % mod;}
ll sqr(ll x){return x * x % mod;}
ll qpow(ll x, ll y){return y ? qpow(sqr(x), y / 2) * (y & 1 ? x : 1) % mod : 1;}
ll n, m, k, a, l, x, y, z, p, res;
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> m >> k >> a >> l;
	res = add(res, a);
	p = 1;
	for(int i = 1; i <= k; i++){
		cin >> x >> y >> z;
		p = mul(p, mul(sub(z, y), qpow(z, mod - 2)));
	}
	res = add(res, p);
	cout << res;
	return 0;
}