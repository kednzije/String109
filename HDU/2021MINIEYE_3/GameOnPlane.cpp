/*
	Author:Frozencode
*/
#include <iostream>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
#define pb push_back
// #define mp make_pair
// #define fi first
// #define se second
typedef long long ll;
// typedef pair<ll,ll> pii;
const ll maxn = 100010;
const ll INF = 2147483647;
ll t, n, det[maxn], minn;
ll x_1, y_1, x_2, y_2;

inline ll gcd(ll a, ll b) {
	ll r = a % b;
	while(r) {
		a = b, b = r, r = a % b;
	}
	return b;
}

struct node{
	ll a, b;
	node() {
		a = b = 0;
	}
	node(ll _a, ll _b) {
		a = _a, b = _b;
		if(a && b) {
			int c = gcd(a, b);
			a /= c, b /= c;
		}
	}
	bool operator < (const node& that) const {
		return a * that.b < b * that.a;
	}
	bool operator == (const node& that) const {
		return a * that.b == b * that.a;
	}
}line[maxn];
// map <double, ll> m;

int e[maxn];

int main()
{
	// freopen("Data.txt", "r", stdin); 
	// freopen("Data.out", "w", stdout);
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		minn = 0; 
		// m.clear();
		// vector <double> lv;
		for(int i = 1; i <= n; i++){
			det[i] = 0;
			scanf("%lld%lld%lld%lld", &x_1, &y_1, &x_2, &y_2);
			// line[i].a = y_2 - y_1;
			// line[i].b = x_2 - x_1;
			line[i] = node(y_2 - y_1, x_2 - x_1);
			// if(!m[line[i].k]) lv.pb(line[i].k);
			// m[line[i].k]++;
		}
		sort(line + 1, line + 1 + n);
		e[0] = 0;
		for(int i = 1; i <= n; i++) {
			if(i == 1 || !(line[i] == line[i - 1])) {
				e[++e[0]] = 1;
			}
			else {
				e[e[0]]++;
			}
		}
		// for(int i = 0; i < lv.size(); i++) e.pb(m[lv[i]]);
		sort(e + 1, e + 1 + e[0]);
		ll pre = 0;
		for(int i = 1; i <= e[0]; i++){
			while(e[i] > minn){
				det[pre + (e[0] - i + 1) * minn + 1] = minn + 1;
				minn++;
			}
			pre += e[i];
			// if(e[i] <= minn) continue;
		}
		pre = 0;
		for(int i = 1; i <= n; i++){
			pre = max(pre, det[i]);
			printf("%d\n", i - pre);
		}
	}
	// cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
	return 0;
}