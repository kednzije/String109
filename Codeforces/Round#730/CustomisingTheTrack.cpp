#include <iostream>
using namespace std;

typedef unsigned long long ull;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		ull sum = 0;
		for(int i = 0; i < n; i++) {
			ull k;
			cin >> k;
			sum += k;
		}
		sum %= n;
		cout << sum * (n - sum) << endl;
	}
	return 0;
}