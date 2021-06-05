#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
constexpr int MAXN = 3e7 + 5;

int prime[MAXN];
bool isPrime[MAXN];
void make() {
	memset(isPrime, true, sizeof(isPrime));

	for(int i = 2; i < MAXN; i++) {
		if(isPrime[i]) {
			prime[++prime[0]] = i;
		}
		for(int j = 1; j <= prime[0] && i * prime[j] < MAXN; j++) {
			isPrime[i * prime[j]] = false;
			if(!(i % prime[j])) {
				break;
			}
		}
	}

	isPrime[1] = false;
}

inline int findAns(int x) {
	if(isPrime[x]) {
		return 1;
	}
	else if(isPrime[2 * x - 1] || isPrime[2 * x + 1]) {
		return 2;
	}
	else {
		return -1;
	}
}

int main() {
	make();
	int t;
	scanf("%d", &t);
	int ans = 0, x = 0;
	while(t--) {
		ans = 0;
		scanf("%d", &x);
		if(x <= 0) {
			ans += 1 - 2 * x;
			x = 1 - x;
			if(isPrime[x]) {
				ans += 1;
			}
			else if(isPrime[2 * x + 1]) {
				ans += 2;
			}
			else {
				x++;
				for(; x < MAXN; x++) {
					if(findAns(x) != -1) {
						ans = 2 * x + findAns(x) - 1;
						break;
					}
				}
			}
		}
		else {
			if(isPrime[x]) {
				ans += 1;
			}
			else if(isPrime[2 * x - 1] || isPrime[2 * x + 1]) {
				ans += 2;
			}
			else {
				for(; x < MAXN; x++) {
					if(findAns(x) != -1) {
						ans = 2 * x + findAns(x) - 1;
						break;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
}