#include <iostream>
using namespace std;
constexpr int MAXN = 1e6 + 10;
using ll = long long;

inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}

ll nums[MAXN];

int main() {
	ll n, m, sum = 0, max_num = -1;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		sum += nums[i];
		max_num = get_max(max_num, nums[i]);
	}
	ll l = 0, r = max_num;
	auto check = [=](int k)->bool {
		ll tmp_sum = 0;
		for(int i = 1; i <= n; i++) {
			tmp_sum += get_max(nums[i] - k, 0);
		}
		return tmp_sum >= m;
	};
	while(l < r) {
		int mid = (l + r + 1) / 2;
		if(check(mid)) {
			l = mid;
		}
		else {
			r = mid - 1;
		}
	}
	cout << l << endl;
}