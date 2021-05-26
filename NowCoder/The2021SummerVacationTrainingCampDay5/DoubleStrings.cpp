#include <iostream>
#include <string>
using namespace std;
constexpr int MAXN = 5005;
constexpr int MOD = 1e9 + 7;
using ll = long long;

ll add(ll a, ll b) {
	return (((a % MOD) + (b % MOD)) % MOD + MOD) % MOD;
}

ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}

pair <ll, ll> dp[2][MAXN];

int main() {
	int n, m;
	string a, b;
	cin >> a >> b;
	n = a.length(), m = b.length();	
	for(int i = 1; i <= n; i++) {
		bool x = i & 1, y = !x;
		for(int j = 1; j <= m; j++) {
			dp[x][j].first = add(add(dp[y][j].first, dp[x][j - 1].first), -dp[y][j - 1].first);
			dp[x][j].second = add(dp[y][j].second, dp[x][j - 1].second);
			if(a[i - 1] == b[j - 1]) {
				dp[x][j].first = add(dp[x][j].first, dp[y][j - 1].first + 1);
			}
			if(a[i - 1] < b[j - 1]) {
				dp[x][j].second = add(dp[x][j].second, dp[y][j - 1].first + 1);
			}
		}
	}
	cout << dp[n & 1][m].second << endl;
}
/*
asdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvlasdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvlasdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvlasdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvlasdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvlasdacjbvlakslkasbclkajnclasknclkasnclkanslcknalknclkasnslcadjviajifouhoirfibasfjasnfjdablvjbalscnjadnlkldknvl
*/