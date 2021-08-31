#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 5e4 + 10;

int n, m, f[MAXN * 3]; // rock, paper, scissors

int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
void merge(int a, int b) { // a > b
	int fa = getf(a), fb = getf(b);
	if(fa != fb) {
		srand(time(NULL));
		if(rand() % 2) {
			f[fa] = fb;
		}
		else {
			f[fb] = fa;
		}
	}
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= 3 * n; i++) {
		f[i] = i;
	}
	int cnt = 0;
	for(int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b; // a > b
		if(a < 1 || a > n || b < 1 || b > n || a == b) {
			cnt++;
		}
		else if(getf(a + n) == getf(b) || getf(a) == getf(b)) {
			cnt++;
		}
		else {
			merge(a, b + n), merge(a + n, b + 2 * n), merge(a + 2 * n, b);
		}
	}
	cout << cnt << endl;
}