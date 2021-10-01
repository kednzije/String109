#include <iostream>
using namespace std;
constexpr int MAXN = 1e4 + 10;

int nums[MAXN];

bool check(int l, int r) {
	if(l >= r) {
		return true;
	}
	int mid = r;
	for(int i = l; i <= r; i++) {
		if(nums[i] > nums[r]) {
			mid = i;
			break;
		}
	}
	for(int i = mid + 1; i <= r; i++) {
		if(nums[i] < nums[r]) {
			return false;
		}
	}
	return check(l, mid - 1) && check(mid, r - 1);
}

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	cout << check(1, n) << endl;
}