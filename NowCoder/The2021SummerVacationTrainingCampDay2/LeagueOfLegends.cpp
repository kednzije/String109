// #include <iostream>
// #include <cstdio>
// #include <cstring>
// #include <utility>
// #include <algorithm>
// using namespace std;
// constexpr int MAXN = 5005;
// inline int max(int a, int b) {
// 	return a > b ? a : b;
// }
// inline int min(int a, int b) {
// 	return a < b ? a : b;
// }

// pair <int, int> freet[MAXN];

// int main() {
// 	memset(freet, 0, sizeof(freet));
// 	int n, k, ans=0;
// 	cin >> n >> k;
// 	for(int i = 1; i <= n; i++) {
// 		cin >> freet[i].first >> freet[i].second;
// 		ans += freet[i].second - freet[i].first;
// 	}
// 	sort(freet + 1, freet + 1 + n);
// 	int merge=0;
// 	auto calc = [&](int i, int j) {
// 		if(min(freet[i].second, freet[j].second) >= max(freet[i].first, freet[j].first)) {
// 			return INT_MAX;
// 		}
// 		return freet[i].second - freet[i].first
// 			+ freet[j].second - freet[j].first
// 			- (min(freet[i].second, freet[j].second) - max(freet[i].first, freet[j].first));
// 	};
// 	while(merge < n - k) {
// 		int choseni=0, chosenj=0;
// 		for(int i = 1; i <= n;) {
// 			// if(freet[i].first < 0) {
// 			// 	continue;
// 			// }
// 			int j = i + 1;
// 			for(; j <= n; j++) {
// 				if(freet[j].first > 0) {
// 					break;
// 				}
// 			}
// 			if(choseni == 0 && chosenj == 0) {
// 				choseni = i, chosenj = j;
// 			}
// 			else if(calc(i, j) < calc(choseni, chosenj)) {
// 				choseni = i, chosenj = j;
// 			}

// 			i = j;
// 		}

// 		ans -= calc(choseni, chosenj);
// 		freet[choseni].first = max(freet[choseni].first, freet[chosenj].first);
// 		freet[choseni].second = min(freet[choseni].second, freet[chosenj].second);
// 		freet[chosenj].first = -1;
// 		merge++;
// 	}
// 	cout << max(ans, 0) << endl;
// }

/*
	Author:Frozencode
*/
#include <iostream>
#include <queue>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 100010;
const ll INF = 2147483647;
ll n, k, res, pos;
bool vis[maxn];
struct node{
	ll x, y, det;
}cur;
bool operator < (const node& a,const node& b)
{
    return a.det < b.det;
}
bool operator > (const node& a,const node& b)
{
    return a.det > b.det;
}
priority_queue <node, vector<node>, greater<node> > q;
struct line{
	ll l, r;
}a[maxn];
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> k;
	pos = n;
	for(int i = 1; i <= n; i++){
		cin >> a[i].l >> a[i].r;
		res += a[i].r - a[i].l;
		a[i].r--;
	}
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			cur.x = i;
			cur.y = j;
			ll minn = min(a[i].r, a[j].r);
			ll maxx = max(a[i].l, a[j].l);
			ll len = minn - maxx + 1;
			if(len <= 0) len = -INF;
			cur.det = a[i].r - a[i].l + 1 + a[j].r - a[j].l + 1 - len;
			q.push(cur);
		}
	}
	//cout << q.top().det;
	for(int i = 1; i <= n - k; i++){
		while(!q.empty()){
			cur = q.top();
			q.pop();
			if(vis[cur.x] || vis[cur.y]) continue;
			++pos;
			res -= cur.det;
			vis[cur.x] = 1;
			vis[cur.y] = 1;
			a[pos].r = min(a[cur.x].r, a[cur.y].r);
			a[pos].l = max(a[cur.x].l, a[cur.y].l);
			for(int j = 1; j < pos; j++){
				if(vis[j]) continue;
				ll minn = min(a[pos].r, a[j].r);
				ll maxx = max(a[pos].l, a[j].l);
				ll len = minn - maxx + 1;
				if(len <= 0) len = -INF;
				cur.det = a[pos].r - a[pos].l + 1 + a[j].r - a[j].l + 1 - len;
				cur.x = j;
				cur.y = pos;
				q.push(cur);
			}
			break;
		}
	}
	if(res < 0) res = 0;
	cout << res;
	return 0;
}