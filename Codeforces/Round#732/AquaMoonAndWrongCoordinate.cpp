#include <iostream>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1005;
typedef long long ll;

ll m, k, pos[MAXN][MAXN], sum[MAXN], sum2[MAXN];

int main() {
	scanf("%lld%lld", &m, &k);
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%lld", &pos[i][j]);
			sum[i] += pos[i][j], sum2[i] += pos[i][j] * pos[i][j];
		}
	}
	int err = 1, delta = sum[2] - sum[1];
	for(int i = 1; i <= k; i++) {
		if(sum[i] != sum[1] + (i - 1) * delta) {
			err = i;
		}
	}
	if(err == k && 2 * sum[k - 1] == sum[k - 2] + sum[k]) {
		if(2 * sum[3] == sum[2] + sum[4]) {
			err = 1;
		}
		else {
			err = 2;
		}
	}
	printf("%d ", err - 1);
	ll sum_v2;
	if(err > k - 3) {
		ll a = sum2[err - 3], b = sum2[err - 2], c = sum2[err - 1];
		sum_v2 = c - 2 * b + a;
	}
	else {
		ll a = sum2[err + 3], b = sum2[err + 2], c = sum2[err + 1];
		sum_v2 = c - 2 * b + a;
	}
	sum_v2 /= 2;
	ll sum_vx;
	if(err >= k - 1) {
		int t = err - 2;
		sum_vx = sum2[t] - sum2[t - 1] - (2 * (t - 1) - 1) * sum_v2;
	}
	else {
		int t = err + 2;
		sum_vx = sum2[t] - sum2[t - 1] - (2 * (t - 1) - 1) * sum_v2;
	}
	sum_vx /= 2;
	ll x; // x = real_pos - pre_pos
	if(err == 1) {
		x = sum[1] - (2 * sum[2] - sum[3]);
	}
	else if(err == k) {
		x = sum[k] - (2 * sum[k - 1] - sum[k - 2]);
	}
	else {
		x = sum[err] - (sum[err - 1] + sum[err + 1]) / 2;
	}
	ll y; // y = real_pos^2 - pre_pos^2;
	y = sum2[err] - sum2[1] - 2 * (err - 1) * sum_vx - (err - 1) * (err - 1) * sum_v2;
	printf("%lld\n", (y / x - x) / 2);
}
/*
5 7 
1 1 1 1 1
2 2 2 2 3 
3 3 3 3 5
4 4 4 4 7
5 5 6 5 9
6 6 6 6 11
7 7 7 7 13
*/