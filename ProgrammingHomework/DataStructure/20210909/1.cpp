#include <iostream>
using namespace std;

int main() {
	int cnt = 0, n, digit;
	cin >> n >> digit;
	for(int i = 1; i <= n; i++) {
		int num = i;
		while(0 != num) {
			cnt += ((num % 10) == digit);
			num /= 10;
		}
	}
	cout << cnt << endl;
}