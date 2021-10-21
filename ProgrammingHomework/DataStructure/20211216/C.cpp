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
#define ls(i) (i * 2)
#define rs(i) (i * 2 + 1)

int h[MAXN];
struct Node {
	ll l, r, max_num, min_num;
} nodes[MAXN * 4];

void build(int l, int r, int i) {
	if(l == r) {
		h[l] = input();
		nodes[i] = { l, r, h[l], h[l] };
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, ls(i)), build(mid + 1, r, rs(i));
	nodes[i] = { 
		l, 
		r, 
		get_max(nodes[ls(i)].max_num, nodes[rs(i)].max_num), 
		get_min(nodes[ls(i)].min_num, nodes[rs(i)].min_num) 
	};
}

int query(int i, int l, int r, int val) {
	if(nodes[i].l == nodes[i].r) {
		return (nodes[i].max_num < val) && (l <= nodes[i].l && nodes[i].r <= r);
	}
	if(l <= nodes[i].l && nodes[i].r <= r && nodes[i].max_num < val) {
		return nodes[i].r - nodes[i].l + 1;
	}
	if(l <= nodes[i].l && nodes[i].r <= r && nodes[i].min_num >= val) {
		return 0;
	}
	int mid = (nodes[i].l + nodes[i].r) / 2, sum = 0;
	if(l <= mid) {
		sum += query(ls(i), l, r, val);
	}
	if(r >= mid + 1) {
		sum += query(rs(i), l, r, val);
	}
	return sum;
}

int ans[MAXN];

int main() {
	int n = input();
	build(1, n, 1);
	// for(int i = 1; i < n; i++) {
	// 	cout << query(1, i + 1, n, h[i]) << ' ';
	// }
	// cout << 0 << endl;
	ans[n] = 0;
	ll max_num = h[n];
	for(int i = n - 1; i >= 1; i--) {
		if(h[i] > max_num) {
			max_num = h[i];
			ans[i] = n - i;
		}
		else {
			ans[i] = query(1, i + 1, n, h[i]);
		}
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
}