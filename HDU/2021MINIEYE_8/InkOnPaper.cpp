#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 5005;
using ll = long long;

inline ll min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll sqr(ll k) {
	return k * k;
}

int n;
pair <ll, ll> points[MAXN];
ll dis[MAXN];

inline ll calc_dis(int i, int j) {
	return sqr(points[i].first - points[j].first) 
		+ sqr(points[i].second - points[j].second);
}

void select(int point_ind, int &min_dis) {
	dis[point_ind] = -1, min_dis = 0;
	for(int i = 1; i <= n; i++) {
		if(dis[i] != -1) {
			dis[i] = min(dis[i], calc_dis(i, point_ind));
			if(dis[min_dis] > dis[i]) {
				min_dis = i;
			}
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		dis[0] = LLONG_MAX;
		for(int i = 1; i <= n; i++) {
			scanf("%lld%lld", &points[i].first, &points[i].second);
			dis[i] = LLONG_MAX;
		}
		int cnt = 0;
		int min_dis = 1;
		ll max_dis = -1;
		while(cnt < n) {
			cnt++;
			select(min_dis, min_dis);
			if(cnt < n) {
				max_dis = max(max_dis, dis[min_dis]);
			}
		}
		printf("%lld\n", max_dis);
	}
}