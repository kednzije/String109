#include <bits/stdc++.h>
using namespace std;

class Solution {
	int get_min(int a, int b) {
		return a < b ? a : b;
	}
public:
    int findKthNumber(int m, int n, int k) {
		int l = 1, r = m * n;
		auto num_cnt = [=](int x)->int {
			int sum = 0;
			for(int i = 1; i <= n; i++) {
				sum += get_min(m, x / i);
			}
			return sum;
		};
		while(l < r) {
			int mid = (l + r) / 2;
			if(num_cnt(mid) < k) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return l;
    }
};

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line;
    while (getline(cin, line)) {
        int m = stringToInteger(line);
        getline(cin, line);
        int n = stringToInteger(line);
        getline(cin, line);
        int k = stringToInteger(line);
        
        int ret = Solution().findKthNumber(m, n, k);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}