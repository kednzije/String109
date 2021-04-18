#include <iostream>
using namespace std;

int q(int i) {
	if(i == 1) {
		return 0;
	}
	return (i - 2) ^ (i - 1);
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
		int n, k;
		cin >> n >> k;
		sol(n);
	}
}