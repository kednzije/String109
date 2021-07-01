#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e6 + 10;
using ll = long long;

inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

inline ll g(ll x) {
	ll sum = 0;
	while(x != 0) {
		sum += x % 10;
		x /= 10;
	}
	return sum;
}

int a, b, c, d, n;

inline ll f(ll x) {
	ll gx = g(x);
	return a * x * x * gx + b * x * x + c * x * gx * gx + d * x * gx;
}

vector <ll> vec[60];

int main() {
	for(int i = 1; i <= 1e6; i++) {
		vec[g(i)].push_back(i);
	}
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &n);
		ll fx_min = LLONG_MAX, _x = -1;
		for(int i = 1; i <= 54; i++) {
			if(vec[i][0] > n) {
				continue;
			}
			if(1 <= vec[i][0] && n >= vec[i][0] && f(vec[i][0]) < fx_min) {
				fx_min = f(vec[i][0]);
				_x = vec[i][0];
			}
			if(1 <= vec[i][vec[i].size() - 1] && n >= vec[i][vec[i].size() - 1] && f(vec[i][vec[i].size() - 1]) < fx_min) {
				fx_min = f(vec[i][vec[i].size() - 1]);
				_x = vec[i][vec[i].size() - 1];
			}

			auto k = upper_bound(vec[i].begin(), vec[i].end(), n);
			k--;
			if(f(*k) < fx_min) {
				fx_min = f(*k);
				_x = *k;
			}

			if(abs(a * i + b) < 1e-6) {
				continue;
			}
			double l = -1.0 * (c * i * i + d * i) / (2 * (a * i + b));
			k = upper_bound(vec[i].begin(), vec[i].end(), l);
			if(f(*k) < fx_min) {
				fx_min = f(*k);
				_x = *k;
			}
			if(k != vec[i].begin()) {
				k--;
				if(f(*k) < fx_min) {
					fx_min = f(*k);
					_x = *k;
				}
			}
		}
		printf("%d\n", fx_min);
	}
}