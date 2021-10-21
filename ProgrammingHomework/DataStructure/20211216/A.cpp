#include <bits/stdc++.h>
using namespace std;

using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	static ll num, sign;
	static char c;
	num = 0, sign = 1;
	c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') {
			sign = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		num = num * 10 + (c - '0');
		c = getchar();
	}
	return sign * num;
}
constexpr ll MAXN = 1e6 + 10;

int dp[MAXN];

int main() {
	string s;
	cin >> s; // MS
	ll ans = 0;
	int l = 0;
	while(s[l++] == 'S');
	for(int i = l; i < s.length(); i++) {
		if(s[i] == 'M') {
			dp[i] = 0;
		}
		else {
			int pos = i - 1;
			while(pos >= l && s[pos] == 'S') {
				if(dp[pos] == 0) {
					break;
				}
				pos -= dp[pos];
			}
			dp[i] = (s[pos] == 'M' ? (i - pos + 1 + dp[pos - 1]) : 0);
		}
		ans = get_max(ans, dp[i]);
	}
	cout << ans << endl;
}