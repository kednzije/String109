#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		long long n;
		cin >> n;
		if(n == 1 || n == 2) {
			cout << 0 << endl;
			continue;
		}
		if(1ll << (long long) log2(n) == n) {
			n -= 1;
		}
		cout << (1ll << (long long) log2(n)) - 1 << endl;
	}
}