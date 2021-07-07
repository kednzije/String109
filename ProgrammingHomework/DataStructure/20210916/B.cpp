#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n, cnt = 0;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		if(n % i == 0 && i % 2 == 1) {
			cnt += (n / i > i / 2);
		}
		if((2 * n) % i == 0 && i % 2 == 0 && i * (n / i) != n) {
			cnt += (n / (i / 2) / 2 > i / 2 - 1);
		}
	}
	cout << cnt << endl;
	return 0;
}