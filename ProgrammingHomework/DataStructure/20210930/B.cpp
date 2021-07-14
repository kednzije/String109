#include <iostream>
using namespace std;
#define INT_MAX 2147483647
constexpr int MAXN = 1e5 + 8;

inline int max(int a, int b) {
	return a > b ? a : b;
}

int nums[MAXN], ans[MAXN], sta[MAXN];

int main() {
	int n = 0, num;
	while(cin >> num) {
		nums[++n] = num;
	}
	nums[0] = INT_MAX;
	int p_sta = 0;
	sta[0] = 0;

	for(int i = n; i >= 1; i--) {
		while(nums[sta[p_sta]] <= nums[i]) {
			p_sta--;
		}
		ans[i] = max(0, sta[p_sta] - i);
		sta[++p_sta] = i;
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
}