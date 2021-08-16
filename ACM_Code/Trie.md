```c++
/*
	Author:Frozencode
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef int ll;
typedef pair<ll,ll> pii;
const ll maxn = 2000010;
const ll INF = 2147483647;
ll n, a[maxn];
struct Trie{
	ll cnt = 0;
	ll son[maxn << 2][2];
	ll l[maxn << 2], r[maxn << 2];
	void init(){
		cnt = 0;
		memset(son, 0, sizeof(son));
	}
	void insert(ll x, ll pos){ // root = 0 
		ll rt = 0;
		for(int i = 30; i >= 0; i--){
			ll op = (x >> i) & 1;
			if(!son[rt][op]) son[rt][op] = ++cnt;
			if(!l[rt]) l[rt] = pos;
			r[rt] = pos;
			rt = son[rt][op];
		}
		if(!l[rt]) l[rt] = pos;
		r[rt] = pos;
	}
	long long get_ans(ll rt, ll x, ll pos){ // pos 指当前点的高度 0是底层
		long long ans = 0;
		for(int i = pos; i >= 0; i--){
			ll op = (x >> i) & 1;
			if(son[rt][op]){
				rt = son[rt][op];
			}
			else{
				ans += (1 << i);
				rt = son[rt][!op];
			}
		}
		return ans;
	}
	void Traceback(int rt){
        printf("%lld %lld\n",l[rt],r[rt]);
        if(son[rt][0]) Traceback(son[rt][0]);
        if(son[rt][1]) Traceback(son[rt][1]);
    }
	long long merge(ll rt, ll pos){
		if(pos == 0) return 0;
		if(son[rt][0] && son[rt][1]){
			long long ans = 2000000000;
			for(int i = l[son[rt][0]]; i <= r[son[rt][0]]; i++) ans = min(ans, get_ans(son[rt][1], a[i], pos - 2) + (1 << (pos - 1)));
			return ans + merge(son[rt][0], pos - 1) + merge(son[rt][1], pos - 1);
		}
		if(son[rt][0]) return merge(son[rt][0], pos - 1);
		if(son[rt][1]) return merge(son[rt][1], pos - 1);
	}
}trie;
int main()
{ 
	ios::sync_with_stdio(false);
	trie.init();
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) trie.insert(a[i], i);
    // trie.Traceback(0);
	cout << trie.merge(0, 31);
	return 0;
}
```

