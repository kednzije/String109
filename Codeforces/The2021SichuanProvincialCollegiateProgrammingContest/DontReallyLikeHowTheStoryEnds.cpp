/*
	Author:Frozencode
*/
#include <iostream>
#include <utility>
#include <set>
#include <cstdio>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 2000010;
const ll INF = 2147483647;
ll t, n, m, x, y, maxx[maxn], s[maxn], tot;
int main() { 
	cin >> t;
	while(t--) {
		ll res = 0;
		tot = 0;
		scanf("%d%d", &n, &m);
		set <pii> im;
		for(int i = 1; i <= n; i++){
			maxx[i] = 0;
			s[i] = 0;
		}
		for(int i = 1; i <= m; i++){
			scanf("%d%d", &x, &y);
			im.insert(mp(x, y));
			im.insert(mp(y, x));
			maxx[x] = max(maxx[x], y);
			maxx[y] = max(maxx[y], x);
		}
		for(int i = 1; i < n; i++){
			s[++tot] = i;
			while(maxx[s[tot]] < i + 1 && tot > 0) tot--;
			if(tot == 0){
				res++;
			}
			else{
				if(im.count(mp(s[tot], i + 1))) continue;
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}