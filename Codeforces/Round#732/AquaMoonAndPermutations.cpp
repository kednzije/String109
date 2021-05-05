#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 505;
constexpr int MOD = 998244353;

long long pow(long long a, long long b) {
	long long res=1;
	while(b) {
		if(b & 1) {
			res = ((res % MOD) * (a % MOD)) % MOD;
		}
		a = ((a % MOD) * (a % MOD)) % MOD, b >>= 1;
	}
	return res;
}

int mat[2*MAXN][MAXN], ans[MAXN], cnt[MAXN][MAXN];
bool vis[2*MAXN];

void init() {
	memset(mat, 0, sizeof(mat));
	memset(ans, 0, sizeof(ans));
	memset(vis, false, sizeof(vis));
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		init();
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= 2*n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &mat[i][j]);
			}
		}
		int p=0;
		for(int ind = 1; ind <= n; ind++) {
			memset(cnt, 0, sizeof(cnt));

			for(int i = 1; i <= 2*n; i++) {
				if(vis[i]) { continue; }
				for(int j = 1; j <= n; j++) {
					int k = mat[i][j];
					cnt[j][k]++;
				}
			}

			p++;
			for(int i = 1; i <= 2*n; i++) {
				if(vis[i]) { continue; }
				for(int j = 1; j <= n; j++) {
					int k = mat[i][j];
					if(cnt[j][k] == 1) {
						ans[ind] = i;
						p--;
						break;
					}
				}
				if(ans[ind] == i) { break; }
				ans[ind] = i;
			}

			for(int i = 1; i <= 2*n; i++) {
				for(int j = 1; j <= n; j++) {
					if(vis[i]) { continue; }
					if(mat[i][j] == mat[ans[ind]][j]) {
						vis[i] = true;
						break;
					}
				}
			}
		}
		printf("%lld\n", pow(2, (long long)p));
		for(int i = 1; i <= n; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
}