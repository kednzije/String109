#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 300;

int f[MAXN];
int getf(int k) {
	if(f[k] != k) {
		f[k] = getf(f[k]);
	}
	return f[k];
}
void merge(int a, int b) {
	a = getf(a), b = getf(b);
	if(a == b) {
		return;
	}
	if(rand() % 2) {
		f[a] = b;
	}
	else {
		f[b] = a;
	}
}

int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		f[i] = i;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			bool is_connected = false;
			cin >> is_connected;
			if(is_connected) {
				merge(i, j);
			}
		}
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		cnt += (getf(i) == i);
	}
	cout << cnt << endl;
}