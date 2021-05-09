#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int k;
		cin >> k;
		cout << (int)ceil(sqrt(k)) << endl;
	}
}