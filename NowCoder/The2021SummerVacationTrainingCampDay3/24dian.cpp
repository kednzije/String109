#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

inline bool equal(double a, double b) {
	return fabs(a - b) < 1e-9;
}

int n, m;
double nums[15];
bool used[15];
vector <vector <int>> ans;

int calc(int cnt, bool fric, double res) {
	if(cnt == 4) {
		if(equal(res, m) && fric) {
			return 1;
		}
		if(equal(res, m) && !fric) {
			return 2;
		}
		return 0;
	}
	if(!equal(res, (int)res)) {
		fric = true;
	}
	int ret = 0;
	for(int i = 1; i <= n; i++) {
		if(used[i]) {
			continue;
		}
		used[i] = true;
		switch(calc(cnt + 1, fric, res + nums[i])) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		switch(calc(cnt + 1, fric, res - nums[i])) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		switch(calc(cnt + 1, fric, res * nums[i])) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		switch(calc(cnt + 1, fric, res / nums[i])) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		switch(calc(cnt + 1, fric, nums[i] - res)) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		switch(calc(cnt + 1, fric, nums[i] / res)) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return 2;
				break;
			case 0: default:
				break;
		}
		used[i] = false;
	}
	for(int i = 1; i <= n; i++) {
		if(used[i]) {
			continue;
		}
		for(int j = i + 1; j <= n; j++) {
			if(used[j]) {
				continue;
			}
			double a = nums[i], b = nums[j];
			nums[j] = a + b, used[i] = true;
			switch(calc(cnt + 1, fric, res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			
			nums[j] = a - b, used[i] = true;
			switch(calc(cnt + 1, fric, res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			
			nums[j] = b - a, used[i] = true;
			switch(calc(cnt + 1, fric, res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			
			nums[j] = a * b, used[i] = true;
			switch(calc(cnt + 1, fric, res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			
			nums[j] = a / b, used[i] = true;
			switch(calc(cnt + 1, fric | !equal(nums[j], (int)nums[j]), res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			
			nums[j] = b / a, used[i] = true;
			switch(calc(cnt + 1, fric | !equal(nums[j], (int)nums[j]), res)) {
				case 1:
					if(!ret) {
						ret = 1;
					}
					break;
				case 2:
					nums[i] = a, nums[j] = b, used[i] = false;
					return 2;
					break;
				case 0: default:
					break;
			}
			nums[i] = a, nums[j] = b, used[i] = false;
		}
	}
	return ret;
}

bool check() {
	used[0] = used[1] = used[2] = used[3] = used[4] = false;
	int ret = 0;
	for(int i = 1; i <= n; i++) {
		used[i] = true;
		switch(calc(1, false, nums[i])) {
			case 1:
				if(!ret) {
					ret = 1;
				}
				break;
			case 2:
				return false;
				break;
			case 0: default:
				break;
		}
		used[i] = false;
	}
	return ret == 1;
}

void dfs(int pos) {
	if(pos == n + 1) {
		if(check()) {
			vector <int> vec;
			for(int i = 1; i <= n; i++) {
				vec.push_back(nums[i]);
			}
			ans.push_back(vec);
		}
		return;
	}
	for(int i = nums[pos - 1]; i <= 13; i++) {
		nums[pos] = i;
		dfs(pos + 1);
	}
}

int main() {
	cin >> n >> m;
	if(n == 1 || n == 2 || m > pow(13, n)) {
		cout << 0 << endl;
		return 0;
	}
	dfs(1);
	printf("%d\n", ans.size());
	for(auto vec: ans) {
		for(auto num: vec) {
			printf("%d ", num);
		}
		printf("\n");
	}
}