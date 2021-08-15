/**
 * @file EulersTotientFunction.cpp
 * @author String
 * @brief 
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
constexpr int MAXN = 50050;

int phi[MAXN], prime[MAXN];
bool vis[MAXN];

inline void make(int n)
{
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= prime[0] && prime[j] * i <= n; j++) {
			vis[prime[j] * i] = true;
			if (!(i % prime[j])) {
				phi[prime[j] * i] = phi[i] * prime[j];
				break;
			}
			else {
				phi[prime[j] * i] = phi[i] * phi[prime[j]];
			}
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	make(n);
	int m;
	scanf("%d", &m);
	while (m--) {
		int k;
		scanf("%d", &k);
		printf("%d\n", phi[k]);
	}
	return 0;
}