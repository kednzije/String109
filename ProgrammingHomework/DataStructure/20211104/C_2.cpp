#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 1e4 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}

int f[MAXN], x[MAXN], y[MAXN], sz[MAXN];
inline int getf(int x) {
	if(f[x] != x) {
		f[x] = getf(f[x]);
		sz[x] = sz[f[x]];
	}
	return f[x];
}
void merge(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if(fa == fb) {
		return;
	}
	srand(time(NULL));
	if(rand() % 2) {
		swap(fa, fb);
	}
	f[fa] = fb;
	sz[fb] += sz[fa];
}

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int pos_x, pos_y;
		cin >> pos_x >> pos_y;
		pos_x++, pos_y++;
		// init
		f[i] = i, sz[i] = 1;
		// merge
		if(x[pos_x] != 0) {
			merge(i, x[pos_x]);
		}
		else {
			x[pos_x] = i;
		}
		if(y[pos_y] != 0) {
			merge(i, y[pos_y]);
		}
		else {
			y[pos_y] = i;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += (f[i] == i ? (sz[i] - 1) : 0);
	}
	cout << ans << endl;
}