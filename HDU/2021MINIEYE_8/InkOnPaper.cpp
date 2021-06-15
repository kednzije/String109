#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
constexpr int MAXN = 5005;
using ll = long long;

ll x[MAXN], y[MAXN];
inline ll calc_time_2(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int f[MAXN];
inline int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
inline void merge(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if(fa != fb) {
		if(rand() % 2) {
			f[fa] = fb;
		}
		else {
			f[fb] = fa;
		}
	}
}

struct Time {
	int i, j;
	ll dis;
	Time() {
		i = j = dis = 0;
	}
	Time(int _i, int _j) {
		i = _i, j = _j;
		dis = calc_time_2(i, j);
	}
	bool operator < (const Time &that) const {
		return dis < that.dis;
	}
} times[MAXN * MAXN];

int main() {
	srand(time(NULL));

	int t;
	scanf("%d", &t);
	while(t--) {
		memset(x, 0, sizeof(x)), memset(y, 0, sizeof(y));
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%lld%lld", &x[i], &y[i]);

			f[i] = i;
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n; j++) {
				times[++cnt] = Time(i, j);
			}
		}
		sort(times + 1, times + 1 + cnt);
		cnt = 0;
		ll min_time = -1;
		for(int k = 1; ; k++) {
			int i = times[k].i, j = times[k].j;
			if(getf(i) != getf(j)) {
				merge(i, j);
				cnt++;

				min_time = min_time > times[k].dis ? min_time : times[k].dis;
			}

			if(cnt == n - 1) {
				break;
			}
		}

		printf("%lld\n", min_time);
	}
}