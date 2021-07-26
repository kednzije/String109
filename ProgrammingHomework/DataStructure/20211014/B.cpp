#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}
constexpr int MAXN = 1e5 + 10;

int num[MAXN], ans[MAXN];

vector <int> make_ans(int l, int r, int from_second) {
	if(l == r) {
		return vector <int> {l};
	}
	if(l + 1 == r) {
		return from_second ? (vector <int> {r, l}) : (vector <int> {l, r});
	}
	int n = r - l + 1, mid = (l + r) / 2;
	vector <int> ans, sub_ans = make_ans((n % 2 ? mid + !from_second : mid + 1), r, (n % 2) ^ from_second);
	for(int i = 0; i < n / 2; i++) {
		if(from_second) {
			ans.push_back(sub_ans[i]), ans.push_back(l + i);
		}
		else {
			ans.push_back(l + i), ans.push_back(sub_ans[i]);
		}
	}
	if(n % 2) {
		ans.push_back(from_second ? sub_ans[n / 2] : l + n / 2);
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> num[i];
	}
	sort(num + 1, num + n);
	vector <int> ans = make_ans(1, n, false);
	for(auto x: ans) {
		cout << num[x] << ' ';
	}
}