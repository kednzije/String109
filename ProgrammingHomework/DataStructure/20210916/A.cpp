#include <iostream>
#include <string>
using namespace std;
constexpr int MAXN = 1e6 + 10;

int sum[2][MAXN];

int main() {
	string s;
	cin >> s;
	int n = s.length();
	for(int i = 0; i < n; i++) {
		if(0 == i) {
			sum[s[i] == '1'][i] = 1;
			sum[s[i] != '1'][i] = 0;
			continue;
		}
		sum[s[i] == '1'][i] = 1 + sum[s[i] == '1'][i - 1];
		sum[s[i] != '1'][i] = sum[s[i] != '1'][i - 1];
	}
	for(int k = 0; k <= n; k++) {
		if((0 == k ? 0 : sum[0][k - 1]) == (n == k ? 0 : (sum[1][n - 1] -  sum[1][k] + (s[k] == '1')))) {
			cout << k << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}