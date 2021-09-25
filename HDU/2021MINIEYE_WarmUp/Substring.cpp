#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
constexpr int MAXN = 4e5 + 50;

inline void get_max(int &a, int b) {
	a = (a > b ? a : b);
}

char str[MAXN];
// int nums[MAXN];
map <char, int> cnt;

int main() {
	int k, n;
	while(scanf("%d%s", &k, str) != EOF) {
		// memset(nums, 0, sizeof(nums));
		n = strlen(str);
		// for(int i = 0; i < n; i++) {
		// 	if(i == 0 || str[i] != str[i - 1]) {
		// 		nums[++nums[0]]++;
		// 	}
		// 	else {
		// 		nums[nums[0]]++;
		// 	}
		// }
		// int ans = 0, cur = 0;
		// for(int i = 1; i <= nums[0]; i++) {
		// 	if(nums[i] > k) {
		// 		get_max(ans, cur + k);
		// 		cur = k;
		// 	}
		// 	else {
		// 		cur += nums[i];
		// 	}
		// }
		cnt.clear();
		int ans = 0, l = 0;
		for(int r = 0; r < n; r++) {
			while(cnt[str[r]] == k) {
				cnt[str[l++]]--;
			}
			cnt[str[r]]++;
			get_max(ans, r - l + 1);
		}
		printf("%d\n", ans);
	}
}