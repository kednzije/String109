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
const ll maxn = 200010;
const ll INF = 2147483647;
ll n, p, q, sum, a[maxn], b[maxn], l = -1, r = INF;
bool check(ll x){
	multiset <ll> s;
	for(int i = 1; i <= q; i++) s.insert(b[i]);
	ll cnt = 0, maxx;
	for(int i = 1; i <= p; i++){
		if(s.empty()) break;
		if(sum - a[i] < a[i] - x) continue;
		maxx = min(sum - a[i], a[i] + x);
		auto it = s.begin();
		it = s.upper_bound(maxx);
		if(it == s.begin()) continue;
		it = prev(it);
		if(*it < a[i] - x) continue;
		ll tem = *it;
		cnt++;
		if((it = s.find(tem)) != s.end()) s.erase(it);
	}
	return cnt >= n;
}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> p >> q >> sum;
	for(int i = 1; i <= p; i++) cin >> a[i];
	sort(a + 1, a + p + 1);
	for(int i = 1; i <= q; i++) cin >> b[i];
	while(l != r - 1){
		ll mid = (l + r) >> 1;
		if(check(mid)){
			r = mid;
		}
		else{
			l = mid;
		}
	}
	cout << (r == INF ? -1 : r);
	return 0;
}