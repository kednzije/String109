#include <iostream>
#include <cmath>
using namespace std;

bool equal(int* arr) {
	return arr[0] == arr[1] && arr[0] == arr[2];
}
bool in(int* arr) {
	return (arr[0] - arr[2]) * (arr[1] - arr[2]) < 0;
}
bool check(int* x, int* y) {
	return (equal(x) && in(y)) || (equal(y) && in(x));
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		int x[3], y[3];
		for(int i = 0; i < 3; i++) {
			cin >> x[i] >> y[i];
		}
		int ans = abs(x[0] - x[1]) + abs(y[0] - y[1]);
		if(check(x, y)) {
			ans += 2;
		}
		cout << ans << endl;
	}
}