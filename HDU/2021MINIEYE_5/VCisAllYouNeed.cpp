#include <iostream>
#include <cstdio>
using namespace std;
using ll = long long;

int main() {
	int t;
	scanf("%d", &t);
	ll n, k;
	while(t--) {
		scanf("%lld%lld", &n, &k);
		if(n <= k + 1) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
}