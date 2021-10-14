#include <iostream>
using namespace std;
constexpr int MAXN = 1e5 + 50;
using ll = long long;
inline int get_max(int a, int b) {
	return a > b ? a : b;
}

ll nums[MAXN];

int main() {
	int n, m, max_num = -1;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		max_num = get_max(max_num, nums[i]);
	}
	auto check = [=](int k)->bool {
		ll sum = 0;
		for(int i = 1; i <= n; i++) {
			sum += (nums[i] + k - 1) / k;
		}
		return sum <= m;
	};
	int l = 1, r = max_num;
	while(l < r) {
		int mid = (l + r) / 2;
		if(check(mid)) {
			r = mid;
		}
		else {
			l = mid + 1;
		}
	}
	cout << l << endl;
}