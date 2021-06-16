#include <iostream>
using namespace std;
using ll = long long;

int main() {
	ll n;
	cin >> n;
	int len = 1;
	ll max_ind = 3;
	for(; max_ind < n; max_ind *= 3, len++) {
		n -= max_ind;
	}
	while(max_ind > 1) {
		if(n <= max_ind / 3) {
			cout << '2';
		}
		else if(n <= max_ind / 3 * 2) {
			cout << '3';
			n -= max_ind / 3;
		}
		else {
			cout << '6';
			n -= max_ind / 3 * 2;
		}
		max_ind /= 3;
	}
	cout << endl;
}