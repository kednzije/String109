#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
using ll = long long;
constexpr ll MAXN = 1e5 + 10;
inline ll get_min(ll a, ll b) {
	return a < b ? a : b;
}
inline ll get_max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll get_abs(ll k) {
	return k > 0 ? k : -k;
}

pair <int, int> atk[2][MAXN];
map <int, pair <int, int>> ind;
bool can_win[MAXN];

void dfs(int k, const int n) {
	can_win[k] = true;
	for(int i = ind[k].first + 1; i <= n; i++) {
		if(!can_win[atk[0][i].second]) {
			dfs(atk[0][i].second, n);
		}
		else {
			break;
		}
	}
	for(int i = ind[k].second + 1; i <= n; i++) {
		if(!can_win[atk[1][i].second]) {
			dfs(atk[1][i].second, n);
		}
		else {
			break;
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int map_ind = 0; map_ind < 2; map_ind++) {
			for(int i = 1; i <= n; i++) {
				scanf("%d", &atk[map_ind][i].first);
				atk[map_ind][i].second = i;
			}
		}
		sort(atk[0] + 1, atk[0] + 1 + n);
		sort(atk[1] + 1, atk[1] + 1 + n);
		for(int i = 1; i <= n; i++) {
			ind[i] = { 0, 0 };
		}
		for(int i = 1; i <= n; i++) {
			ind[atk[0][i].second].first = i;
			ind[atk[1][i].second].second = i;
		}

		// only one can win
		if(atk[0][n].second == atk[1][n].second) {
			for(int i = 1; i <= n; i++) {
				putchar('0' + (i == atk[0][n].second));
			}
			putchar('\n');
			continue;
		}

		memset(can_win, false, sizeof(can_win));

		// can_win[atk[0][n].second] = can_win[atk[1][n].second] = true;
		// for(int i = ind[atk[0][n].second].first; i <= n; i++) {
		// 	can_win[i] = true;
		// }
		// for(int i = ind[atk[1][n].second].second; i <= n; i++) {
		// 	can_win[i] = true;
		// }
		dfs(atk[0][n].second, n), dfs(atk[1][n].second, n);
		for(int i = 1; i <= n; i++) {
			putchar('0' + can_win[i]);
		}
		putchar('\n');
	}
}