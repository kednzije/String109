#include <iostream>
using namespace std;
using ll = long long;

int main() {
	int t;
	cin >> t;
	while(t--) {
		ll n, m, k;
		cin >> n >> m >> k;
		if(m < n - 1 || m > n * (n - 1) / 2) {
			cout << "NO" << endl;
			continue;
		}
		if(k == 0) {
			cout << "NO" << endl;
			continue;
		}
		if(k == 1 || k == 2) {
			cout << (n == 1 ? "YES" : "NO") << endl;
			continue;
		}
		if(n == 1 || n == 2) {
			cout << "YES" << endl;
			continue;
		}
		if(k == 3) {
			cout << (m == n * (n - 1) / 2 ? "YES" : "NO") << endl;
			continue;
		}
		cout << "YES" << endl;
	}
}