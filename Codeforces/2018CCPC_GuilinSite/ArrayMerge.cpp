#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5 + 10;
using ll = long long;

ll a[MAXN], b[MAXN];

int main() {
	int T;
	cin >> T;
	for(int ind = 1; ind <= T; ind++) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		int n, m;
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = 1; i <= m; i++) {
			cin >> b[i];
		}
		int x = 1, y = 1;
		ll ans = 0;
		while(x <= n || y <= m) {
			if(x > n) {
				ans += b[y] * (y + n);
				y++;
			}
			else if(y > m) {
				ans += a[x] * (x + m);
				x++;
			}
			else if(a[x] > b[y]) {
				ans += a[x] * (x + y - 1);
				x++;
			}
			else if(a[x] < b[y]) {
				ans += b[y] * (x + y - 1);
				y++;
			}
			else {
				for(int i = x, j = y; i <= n && j <= m; i++, j++) {
					
				}
			}
		}
		printf("Case %d: %lld\n", ind, ans);
	}
}