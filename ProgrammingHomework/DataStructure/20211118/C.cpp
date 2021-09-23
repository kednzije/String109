#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e2 + 10;

int n, a, pos_a, nums[MAXN];
int log_2(int k) {
	int cnt = 0;
	while (k) {
		cnt++;
		k >>= 1;
	}
	return cnt - 1;
}

int main() {
	cin >> a >> n;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		if(nums[i] == a) {
			pos_a = i;
		}
	}
	int depth = log_2(n) + 1;
	bool will_win;
	// cout << ((pos_a % 2) ? "true" : "false") << endl;
	if(pos_a % 2) {
		if(pos_a != 1) {
			will_win = true;
		}
		else {
			will_win = (n < (1 << depth) - 2);
		}
	}
	else {
		int depth_a = log_2(pos_a) + 1;
		// int a_cnt = (1 << (depth - 1) - 1) - min(n - (1 << (depth - 1)) + 1 - (1 << (depth - 2)), 0);
		int a_cnt = (1 << (depth - depth_a + 1)) - 1 - min(n - (1 << (depth - 1)) + 1 - (1 << (depth - 2)), 0);
		// cout << a_cnt << endl;
		will_win = (n - a_cnt) > a_cnt;
	}
	cout << (will_win ? "true" : "false") << endl;
}