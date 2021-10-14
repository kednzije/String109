#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 3e3 + 50;

int f[MAXN * 2];
int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
void merge(int a, int b) {
	a = getf(a), b = getf(b);
	if(a != b) {
		if(rand() % 2) {
			f[a] = b;
		}
		else {
			f[b] = a;
		}
	}
}

int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	for(int i = 1; i <= 2 * n; i++) {
		f[i] = i;
	}
	int u, v;
	while(cin >> u >> v) {
		merge(u, v + n);
		merge(u + n, v);
	}
	bool good = true;
	for(int i = 1; i <= n; i++) {
		good &= (getf(i) != getf(i + n));
	}
	cout << good << endl;
}