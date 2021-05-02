#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int MAXN = 5005;
typedef long long ll;

ll dp[2][MAXN][MAXN], ai, bi, ci;
ll min(ll a, ll b) {
	return a < b ? a : b;
}
ll max(ll a, ll b) {
	return a > b ? a : b;
}
ll max(ll a, ll b, ll c) {
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int main() {
	int n, a, b, c;
	scanf("%d%d%d%d", &n, &a, &b, &c);
	for(int s = 1; s <= n; s++) {
		int pre = (s + 1) % 2, now = s % 2;
		scanf("%lld%lld%lld", &ai, &bi, &ci);
		for(int i = 0; i <= min(s, a); i++) {
			for(int j = 0; j <= min(s - i, b); j++) {
				if(s - i - j > c) {
					continue;
				}
				dp[now][i][j] = max(
					(i > 0 ? dp[pre][i - 1][j] + ai : 0), 
					(j > 0 ? dp[pre][i][j - 1] + bi : 0), 
					(s - i - j > 0 ? dp[pre][i][j] + ci : 0));
			}
		}
	}
	printf("%lld\n", dp[n % 2][a][b]);
}