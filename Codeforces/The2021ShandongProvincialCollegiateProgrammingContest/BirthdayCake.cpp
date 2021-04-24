/*
	Author:Frozencode
*/
// #include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pii;
const ll maxn = 500010;
const ll INF = 2147483647;
const ll mod1 = 1000000009;
const ll mod2 = 998244353;
const ll base = 12289;
ll h1[maxn], p1[maxn], h2[maxn], p2[maxn];
ll n, res;
string a[maxn];
map <pii, ll> m;
ll get1_hash(ll l, ll r){
	return (h1[r] - ((h1[l - 1] * p1[r - l + 1]) % mod1) + mod1) % mod1;
}
ll get2_hash(ll l, ll r){
	return (h2[r] - ((h2[l - 1] * p2[r - l + 1]) % mod2) + mod2) % mod2;
}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++){
		p1[0] = 1;
		h1[0] = 0;
		p2[0] = 1;
		h2[0] = 0;
		ll len = a[i].length();
		for(int j = 1; j <= len; j++){
			h1[j] = (h1[j - 1] * base + (a[i][j - 1] - 'a' + 1)) % mod1; //h[1]是头
			p1[j] = p1[j - 1] * base % mod1;
			h2[j] = (h2[j - 1] * base + (a[i][j - 1] - 'a' + 1)) % mod2; //h[1]是头
			p2[j] = p2[j - 1] * base % mod2;
		}
		res += m[mp(h1[len], h2[len])];
		m[mp(h1[len], h2[len])]++;
		for(int j = 1; j <= len / 2; j++){
			ll numx = get1_hash(1, j), numy = get1_hash(len - j + 1, len);
			ll numix = get2_hash(1, j), numiy = get2_hash(len - j + 1, len);
			if(numx == numy && numix == numiy){
				ll mid1 = get1_hash(j + 1, len - j), mid2 = get2_hash(j + 1, len - j);
				res += m[mp(mid1, mid2)];
			}
		}
	}
	cout << res;
	return 0;
}