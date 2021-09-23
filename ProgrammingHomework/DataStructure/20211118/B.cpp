#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int f[MAXN];
int getf(int k) {
	if(k != f[k]) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
void merge(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if(rand() % 2) {
		f[fa] = fb;
	}
	else {
		f[fb] = fa;
	}
}

int main() {
	srand(time(NULL));
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		f[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += (f[i] == i);
	}
	cout << ans - 1 << endl;
}