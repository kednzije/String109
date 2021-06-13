#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
constexpr int MAXN = 1e5 + 5;
using ll = long long;

inline bool equ(double a, double b) {
	return fabs(a - b) <= 1e-7;
}

int n, f[MAXN], ind[MAXN], ans_log[MAXN];
ll sum[MAXN];
 
double limit = -1;
void init() {
	memset(f, 0, sizeof(f));
	memset(ind, 0, sizeof(ind));
	memset(ans_log, -1, sizeof(ans_log));
	memset(sum, 0, sizeof(sum));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &f[i]);
	}
	limit = -1;
}

bool dfs(int x, int from) {
	sum[x] = sum[from] + x, ind[x] = ind[from] + 1;
	if(sum[f[x]] != 0) {
		if(ans_log[f[x]] != -1) {
			ans_log[x] = ans_log[f[x]];
			return ans_log[f[x]];
		}
		double lim = 1.0 * (sum[x] - sum[f[x]] + f[x]) / (ind[x] - ind[f[x]] + 1);
		if(equ(limit, -1)) {
			limit = lim;
		}
		ans_log[x] = equ(limit, lim);
		return ans_log[x];
	}
	ans_log[x] = dfs(f[x], x);
	return ans_log[x];
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		init();
		bool equ = true;
		for(int i = 1; i <= n; i++) {
			if(sum[i] == 0 && !dfs(i, 0)) {
				equ = false;
				break;
			}
		}
		if(equ) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
}