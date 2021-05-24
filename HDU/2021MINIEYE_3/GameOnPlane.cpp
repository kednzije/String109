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
#define mp make_pair
#define fi first
#define se second
typedef int ll;
typedef pair<ll,ll> pii;
const ll maxn = 100010;
const ll INF = 2147483647;
ll t, n, res[maxn], det[maxn], minn;
int x_1, y_1, x_2, y_2;
struct node{
	ll a, b;
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
			scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
			line[i].a = y_2 - y_1;
			line[i].b = x_2 - x_1;
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
			if(e[i] <= minn) continue;
		}
		pre = 0;
		for(int i = 1; i <= n; i++){
			pre = max(pre, det[i]);
			res[i] = i - pre;
			printf("%d\n", res[i]);
		}
	}
	// cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
	return 0;
}