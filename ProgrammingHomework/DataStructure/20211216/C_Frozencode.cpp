#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	static ll num, sign;
	static char c;
	num = 0, sign = 1;
	c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') {
			sign = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		num = num * 10 + (c - '0');
		c = getchar();
	}
	return sign * num;
}

constexpr ll MAXN = 1e5 + 10;

ll n, a[MAXN], b[MAXN], ind[MAXN], ans[MAXN], BIT[MAXN];
ll lowbit(ll x) {
	return x & (-x);
}
ll query(ll x) {
	ll res = 0;
	while(x) {
		res += BIT[x];
		x -= lowbit(x);
	}
	return res;
}
void add(ll x) {
	while(x <= n) {
		BIT[x]++;
		x += lowbit(x);
	}
}

int main() {
	n = input();
	for(int i = 1; i <= n; i++){
		a[i] = b[i] = input();
	}
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++) {
		ind[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
	}
	for(int i = n; i >= 1; i--) {
		ans[i] = query(ind[i] - 1);
		add(ind[i]);
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
	return 0;
}