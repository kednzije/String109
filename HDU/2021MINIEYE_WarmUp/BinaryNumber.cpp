#include <iostream>
#include <cstring>
#include <string>
using namespace std;
constexpr int MAXN = 2e6 + 50;
using ll = long long;

string strs[2];
int most_right_bit[2];

ll steps(int whichstr) {
	ll sum = 0, len = strs[whichstr].length();
	most_right_bit[whichstr] = 0;
	for(int i = 0; i < strs[whichstr].length(); i++) {
		if(strs[whichstr][i] == '1') {
			sum += len - i;
			if(most_right_bit[whichstr] == 0) {
				most_right_bit[whichstr] = len - i;
			}
		}
	}
	return sum;
}

int main() {
	// ios::sync_with_stdio(false);
	while(cin >> strs[0] >> strs[1]) {
		ll s[2];
		for(int i = 0; i < 2; i++) {
			s[i] = steps(i);
		}
		if(s[0] >= s[1]) {
			cout << s[0] - s[1] << endl;
		}
		else {
			ll tmp_ans;
			for(int p = 1; p <= most_right_bit[0]; p++) {
				tmp_ans = s[0] - s[1] + p * (p - 1) / 2 - p + 1;
				if(tmp_ans >= 0) {
					cout << tmp_ans << endl;
					break;
				}
			}
		}
	}
}