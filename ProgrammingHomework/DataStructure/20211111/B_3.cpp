#include <iostream>
#include <map>
#include <vector>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int nums[MAXN], ans[MAXN];
map <int, vector<int>> vals;

int main() {
	int n, a, b;
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++) {
		cin >> nums[i];
		if(vals.count(a - nums[i]) && vals[a - nums[i]].size()) {
			ans[i] = ans[vals[a - nums[i]].back()] = 0;
			vals[a - nums[i]].pop_back();
			if(vals[a - nums[i]].empty()) {
				vals.erase(a - nums[i]);
			}
		}
		else if(vals.count(b - nums[i]) && vals[b - nums[i]].size()) {
			ans[i] = ans[vals[b - nums[i]].back()] = 1;
			vals[b - nums[i]].pop_back();
			if(vals[b - nums[i]].empty()) {
				vals.erase(b - nums[i]);
			}
		}
		else {
			vals[nums[i]].push_back(i);
		}
	}
	for(auto &val: vals) {
		if(val.first * 2 == a || val.first * 2 == b) {
			for(auto ind: val.second) {
				ans[ind] = (val.first == b);
			}
		}
	}
	cout << vals.empty() << endl;
	if(vals.empty()) {
		for(int i = 1; i <= n; i++) {
			cout << ans[i];
			if(i < n) {
				cout << ' ';
			}
		}
	}
}