#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int a, b;
		cin >> a >> b;
		int k = abs(a - b);
		if(k) {
			cout << k << ' ' << min(a % k, k - a % k) << endl;
		}
		else {
			cout << "0 0" << endl;
		}
	}
	return 0;
}