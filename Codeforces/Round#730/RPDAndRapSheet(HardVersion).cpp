#include <iostream>
using namespace std;
const int LEN = 10;
int k;

int sub(int x, int y) {
	int z = 0, p = 1;
	while (x > 0 || y > 0) {
		int a = x % k; x = x / k;
		int b = y % k; y = y / k;
		int c = (a - b + k) % k;
		z += p * c;
		p *= k;
	}
	return z;
}

int q(int i) {
	if(i == 1) {
		return 0;
	}
	if(i % 2) {
		return sub(i - 1, i - 2);
	}
	else {
		return sub(i - 2, i - 1);
	}
}

void sol(int n) {
	for(int i = 1; i <= n; i++) {
		cout << q(i) << endl;
		cout.flush();
		int r;
		cin >> r;
		if(r) { return; }
	}
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n >> k;
		sol(n);
	}
}