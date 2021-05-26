#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
using ll = long long;
constexpr int MAXN = 305;
constexpr ll INF = 22337203685477580;
inline ll sqr(const ll& k) {
	return k * k;
}
inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

struct Jewel {
	ll x, y, z, v;
	Jewel() {}
	Jewel(ll _x, ll _y, ll _z, ll _v) {
		x = _x, y = _y, z = _z, v = _v;
	}
	ll strength(int t) const {
		return sqr(x) + sqr(y) + sqr(z + t * v);
	}
	bool operator < (const Jewel& that) const {
		// return strength(0) < that.strength(0);
		return v > that.v;
	}
} jewels[MAXN];

bool gotten[MAXN];
int n;
ll ans = INF;

void dfs(int cnt, ll tot, ll mini) {
	if(tot + mini >= ans) {
		return;
	}
	if(cnt > n) {
		ans = tot;
		return;
	}
	for(int i = 1; i <= n; i++) {
		if(gotten[i]) {
			continue;
		}
		gotten[i] = true;
		dfs(cnt + 1, tot + jewels[i].strength(cnt - 1), mini - jewels[i].strength(cnt - 1));
		gotten[i] = false;
		mini += jewels[i].strength(cnt) - jewels[i].strength(cnt - 1);
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	clock_t startTime, endTime;
	startTime = clock();
	scanf("%d", &n);
	ll mini = 0;
	for(int i = 1; i <= n; i++) {
		int x, y, z, v;
		scanf("%d%d%d%d", &x, &y, &z, &v);
		jewels[i] = Jewel(x, y, z, v);
		mini += jewels[i].strength(0);
	}
	sort(jewels + 1, jewels + 1 + n);
	dfs(1, 0, mini);
	printf("%lld\n", ans);
	endTime = clock();
	printf("The Run Time is %lfs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}