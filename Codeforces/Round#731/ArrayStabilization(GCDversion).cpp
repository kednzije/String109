#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define ls (i*2)
#define rs (i*2+1)
const int MAXSIZE = 4e5 + 5;

struct Node {
	int l, r, val;
} nodes[MAXSIZE * 4];


int n, nums[MAXSIZE];

inline int gcd(int x, int y) {
	int r = x % y;
	while(r) {
		x = y, y = r;
		r = x % r;
	}
	return y;
}

void build_up(const int i, const int l, const int r) {
	if(l == r) {
		if(l <= n) {
			nodes[i] = {l, r, nums[l]};
		}
		else {
			nodes[i] = {l, r, nums[l - n]};
		}
		return;
	}
	int mid = (l + r) / 2;
	build_up(ls, l, mid), build_up(rs, mid + 1, r);
	nodes[i] = {l, r, gcd(nodes[ls].val, nodes[rs].val)};
}
int query(const int i, const int l, const int r) {
	if(l == nodes[i].l && r == nodes[i].r) {
		return nodes[i].val;
	}
	int mid = (nodes[i].l + nodes[i].r) / 2;
	if(r <= mid) {
		return query(ls, l, r);
	}
	if(l > mid) {
		return query(rs, l, r);
	}
	return gcd(query(ls, l, mid), query(rs, mid + 1, r));
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(nums, 0, sizeof(nums));
		for(int i = 1; i <= n; i++) {
			scanf("%d", &nums[i]);
		}
		build_up(1, 1, 2 * n);
		int l = 0, r = n - 1;
		auto check = [&](int k) {
			int should = query(1, 1, 1 + k);
			for(int i = 2; i <= n; i++) {
				if(query(1, i, i + k) != should) {
					return false;
				}
			}
			return true;
		};
		while(l < r) {
			int mid = (l + r) / 2;
			if(check(mid)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		printf("%d\n", l);
	}
}