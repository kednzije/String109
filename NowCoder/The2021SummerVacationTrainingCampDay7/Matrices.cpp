#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
constexpr int MAXN = 505;
using ll = long long;
constexpr ll MOD = 998244353;

int n, d;
double mat[MAXN][MAXN][MAXN];
ll calc(int k) {
	for(int ind = 1; ind <= n; ind++) {
		for(int i = ind + 1; i <= n; i++) {
			double rat = mat[k][i][ind] / mat[k][ind][ind];
			for(int j = ind; j <= n; j++) {
				mat[k][i][j] -= rat * mat[k][ind][j];
			}
		}
	}
	double res = 1;
	for(int i = 1; i <= n; i++) {
		res *= mat[k][i][i];
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &d);
	for(int k = 0; k <= d; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%lf", &mat[k][i][j]);
			}
		}
	}
	for(int k = 0; k <= n * d; k++) {

	}
}