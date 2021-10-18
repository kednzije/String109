#include <iostream>
#include <cstdio>
using namespace std;
using ll = long long;
constexpr ll MAXN = 1e5 + 10;
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_abs(ll k) {
	return k > 0 ? k : -k;
}

int nums[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, peak, valley;
		scanf("%d%d%d", &n, &peak, &valley);
		if(peak + valley > n - 2 || get_abs(peak - valley) > 1) {
			printf("-1\n");
			continue;
		}
		if(n == 2) {
			printf("1 2\n");
			continue;
		}
		if(peak == 0 && valley == 0) {
			for(int i = 1; i <= n; i++) {
				nums[i] = i;
			}
		}
		else if(peak == 0) {
			nums[1] = n;
			for(int i = 2; i <= n; i++) {
				nums[i] = i - 1;
			}
		}
		else if(valley == 0) {
			for(int i = 1; i < n; i++) {
				nums[i] = i + 1;
			}
			nums[n] = 1;
		}
		// n >= 3
		else if(peak > valley) {
			nums[1] = 2, nums[2] = 3, nums[3] = 1;
			for(int i = 4; i <= n; i++) {
				// nums[i] = i + (i % 2 == 0 ? 1 : -1);
				if(i <= 2 * peak - 1) {
					nums[i] = i + (i % 2 == 0 ? 1 : -1);
				}
				else {
					nums[i] = n - i + 2 * peak;
				}
			}
			if(nums[n] > n) {
				nums[n] = n;
			}
		}
		else if(peak < valley) {
			for(int i = 1; i <= n; i++) {
				// nums[i] = i + (i % 2 == 0 ? -1 : 1);
				if(i <= 2 * valley) {
					nums[i] = i + (i % 2 == 0 ? -1 : 1);
				}
				else {
					nums[i] = i;
				}
			}
			if(nums[n] > n) {
				nums[n] = n;
			}
		}
		else {
			for(int i = 1; i <= n; i++) {
				// nums[i] = i + (i % 2 == 0 ? -1 : 1);
				if(i <= 2 * peak) {
					nums[i] = i + (i % 2 == 0 ? -1 : 1);
				}
				else {
					nums[i] = n - i + 2 * peak + 1;
				}
			}
			if(nums[n] > n) {
				nums[n] = n;
			}
		}
		for(int i = 1; i <= n; i++) {
			printf("%d ", nums[i]);
		}
		printf("\n");
	}
	return 0;
}