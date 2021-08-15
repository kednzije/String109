/**
 * @file CRT.cpp
 * @author String
 * @brief 
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
constexpr int MAXN = 15;
using ll = long long;
 
int n;
ll a[MAXN], b[MAXN];
inline ll add(ll a, ll b, ll p) {
    ll res = 0;
    while(b) {
        if(b & 1) {
			res = ((res % p) + (a % p)) % p;
		}
        a = ((a % p) + (a % p)) % p;
        b >>= 1;
    }
    return res;
}
inline void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d) {
    if(!b) {
        d = a, x = 1, y = 0;
        return;
    }
    ex_gcd(b, a % b, y, x, d);
    y -= (a / b) * x;
}
inline ll inv(ll a, ll b) {
    ll d, x, y;
    ex_gcd(a, b, x, y, d);
    return (d == 1) ? (x % b + b) % b : -1;
}
ll CRT() {
    ll M = 1;
    for(int i = 1;i <= n;i++) {
        M *= b[i];
    }
    ll ans = 0;
    for(int i = 1;i <= n;i++) {
        ans = ((ans % M) + add(add(a[i],  M / b[i], M),  inv(M / b[i], b[i]), M) % M) % M;
    }
    return ans;
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1;i <= n;i++) {
        scanf("%lld", &a[i]);
    }
    for(int i = 1;i <= n;i++) {
        scanf("%lld", &b[i]);
    }
    printf("%lld\n", CRT());
    return 0;
}