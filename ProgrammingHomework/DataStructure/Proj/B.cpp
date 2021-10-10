#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <cerrno>
#include <iterator>
#include <bitset>
using namespace std;
using ll = long long;
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll input() {
	ll num = 0, sign = 1;
	char c = getchar();
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
constexpr ll MAXN = 1e7 + 50;

int buckets[MAXN];

int main() {
	int n, m, num, now_ind = -1, now_num = -1;
	// cin >> m >> n;
	// scanf("%d%d", &m, &n);
	m = input(), n = input();
	for(int i = 0; i < n; i++) { // Why i can't begin from 1 ??
		// cin >> num;
		// scanf("%d", &num);
		num = input();
		buckets[num]++;

		// int k = (i + m - 1) / m; // select the kth maximum num
		
		if(i == 0) {
			now_num = num, now_ind = 1;
		}
		else {
			if(i % m == 0) { // last selected num is the (k - 1)th
				if(num <= now_num) {
					now_ind++;
					if(now_ind > buckets[now_num]) {
						while(buckets[--now_num] == 0);
						now_ind = 1;
					}
				}
			}
			else { // last selected num is the kth
				if(num > now_num) {
					now_ind--;
					if(now_ind == 0) {
						while(buckets[++now_num] == 0);
						now_ind = buckets[now_num];
					}
				}
			}
		}
		printf("%d ", now_num);
	}
	return 0;
}