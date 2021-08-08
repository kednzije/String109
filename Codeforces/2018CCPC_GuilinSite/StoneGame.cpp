/*
	Author:Frozencode
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 500010;
const ll INF = 2147483647;
ll t, n, a[maxn], c[maxn];
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n;
		for(int j = 1; j <= n; j++) cin >> a[j];
		c[1] = 0;
		for(int j = 2; j <= n; j++) c[j] = (a[j] > a[j - 1] ? 1 : -1) + c[j - 1];
		ll res = 0;
		for(int j = 1; j <= n; j++) res += a[j] - c[j];
		cout << "Case " << i << ": ";	
		cout << (res & 1 ? "Alice" : "Bob") << endl;
	}
	return 0;
}