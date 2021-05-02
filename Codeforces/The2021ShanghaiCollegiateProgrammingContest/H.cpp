#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 5;
const long long INF = 3e9 + 10;

struct Car {
	long long p, v, k;
	bool operator < (const Car& that) {
		return p > that.p;
	}
} cars[MAXN];
int sta[MAXN], pre[MAXN], post[MAXN];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%lld%lld%lld", &cars[i].p, &cars[i].v, &cars[i].k);
	}
	sort(cars, cars + n);
	memset(sta, 0, sizeof(sta));
	for(int i = 0; i < n; i++) {
		while(sta[0] && cars[sta[sta[0]]].k == cars[i].k) {
			sta[0]--;
		}
		if(sta[0]) {
			pre[i] = sta[sta[0]];
		}
		else {
			pre[i] = -1;
		}
		sta[++sta[0]] = i;
	}
	memset(sta, 0, sizeof(sta));
	for(int i = n - 1; i >= 0; i--) {
		while(sta[0] && cars[sta[sta[0]]].k == cars[i].k) {
			sta[0]--;
		}
		if(sta[0]) {
			post[i] = sta[sta[0]];
		}
		else {
			post[i] = -1;
		}
		sta[++sta[0]] = i;
	}
	auto crash = [&](long long t) {
		for(int i = 0; i < n; i++) {
			if(pre[i] != -1) {
				long long p1 = cars[pre[i]].p, p2 = cars[i].p, v1 = cars[pre[i]].v, v2 = cars[i].v;
				if(p1 - p2 <= t * (v2 - v1)) {
					return true;
				}
			}
			if(post[i] != -1) {
				long long p1 = cars[i].p, p2 = cars[post[i]].p, v1 = cars[i].v, v2 = cars[post[i]].v;
				if(p1 - p2 <= t * (v2 - v1)) {
					return true;
				}
			}
		}
		return false;
	};
	long long l=0, r=INF;
	if(!crash(r)) {
		printf("-1\n");
		return 0;
	}
	while(l < r) {
		long long mid = (l + r + 1) / 2;
		if(crash(mid)) {
			r = mid - 1;
		}
		else {
			l = mid;
		}
	}
	printf("%lld\n", l);
	return 0;
}