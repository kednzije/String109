#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int f[MAXN];
int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
bool merge(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if(fa == fb) {
		return false;
	}
	if(rand() % 2) {
		f[fa] = fb;
	}
	else {
		f[fb] = fa;
	}
	return true;
}

int main() {
	int m;
	cin >> m;
	for(int i = 1; i < MAXN; i++) {
		f[i] = i;
	}
	srand(time(NULL));
	for(int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		if(!merge(a, b)) {
			cout << a << ' ' << b << endl;
		}
	}
}