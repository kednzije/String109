#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
constexpr int MAXN = 3e4 + 50;

int prime[MAXN];
bool vis[MAXN];

inline void make(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			prime[++prime[0]] = i;
		}
		for (int j = 1; j <= prime[0] && prime[j] * i <= n; j++) {
			vis[prime[j] * i] = true;
			if (!(i % prime[j])) {
				break;
			}
		}
	}
}

double dp[MAXN];

int main() {
	make(3e4 + 1);
	double log_e = log(2.718281828);

	for(int j = 1; j <= 3e4; j++) {
		dp[j] = 0;
	}
	for(int i = 1; i <= prime[0]; i++) { // index of obj
		static double log_p;
		log_p = log(prime[i]);
		for(int j = 3e4; j >= 1; j--) { // size of bag
			// if(j >= prime[i]) {
			// 	dp[j] = max(dp[j], dp[j - prime[i]] + log(prime[i]) * log(2.718281828));
			// }
			static int pow_k;
			pow_k = prime[i];
			for(int k = 1; k <= 3e4; k++) { // times
				if(j >= pow_k && pow_k > 0) {
					dp[j] = max(dp[j], dp[j - pow_k] + k * log_p * log_e);
				}
				else {
					break;
				}
				pow_k *= prime[i];
			}
		}
	}

	int T;
	scanf("%d", &T);
	while(T--) {
		static int n;
		cin >> n;
		printf("%.10lf\n", dp[n]);
	}

	// freopen("Tab.txt", "w", stdout);

	// for(int i = 1; i <= 3e4; i++) {
	// 	if(fabs(dp[i] - dp[i - 1]) <= 1e-8 && i > 0) {
	// 		printf("-1,");
	// 		continue;
	// 	}
	// 	printf("%.10lf,", dp[i]);
	// }
}