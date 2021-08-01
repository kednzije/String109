#include <iostream>
using namespace std;
constexpr int MAXN = 1e7;
inline int max(int a, int b) {
	return a > b ? a : b;
}

int nums[MAXN];
pair <int, int> maxSum(int l, int r, int &maxsum) {
	if(l == r) {
		maxsum = nums[l];
		return make_pair(l, r);
	}
	int mid = (l + r) / 2, tmp_sum[] = { INT_MIN, INT_MIN, 0, 0 }, tmp_pos[] = { 0, 0 };
	for(int i = mid, sum = 0; i >= l; i--) {
		sum += nums[i];
		// tmp_sum[0] = max(tmp_sum[0], sum);
		if(sum > tmp_sum[0]) {
			tmp_sum[0] = sum;
			tmp_pos[0] = i;
		}
	}
	for(int i = mid + 1, sum = 0; i <= r; i++) {
		sum += nums[i];
		// tmp_sum[1] = max(tmp_sum[1], sum);
		if(sum > tmp_sum[1]) {
			tmp_sum[1] = sum;
			tmp_pos[1] = i;
		}
	}
	pair <int, int> tmp_pair[] = { maxSum(l, mid, tmp_sum[2]), maxSum(mid + 1, r, tmp_sum[3])};
	maxsum = max(tmp_sum[0] + tmp_sum[1], max(tmp_sum[2], tmp_sum[3]));
	return (tmp_sum[2] > tmp_sum[3] 
		? (tmp_sum[0] + tmp_sum[1] > tmp_sum[2] ? make_pair(tmp_pos[0], tmp_pos[1]) : tmp_pair[0])
		: (tmp_sum[0] + tmp_sum[1] > tmp_sum[3] ? make_pair(tmp_pos[0], tmp_pos[1]) : tmp_pair[1]));
} 

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
	}
	int maxsum;
	pair <int, int> section = maxSum(1, n, maxsum);
	cout << "Max sum of sub-array is " << '[' << section.first << ',' << section.second << ']' << ": " << maxsum << endl;
}
/*
Input:
16
13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7
Output:
Max sum of sub-array is [8,11]: 43
*/