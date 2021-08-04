#include <iostream>
using namespace std;
#define EPS 1e-7

int main() {
	int n;
	double p;
	cin >> n >> p;
	for(int i = 0; i <= n; i++) {
		if(3.0 * i * (i - 1) * (n - i) + 1.5 * i * (n - i) * (n - i - 1) + i * (i - 1) * (i - 2) - p * n * (n - 1) * (n - 2) >= -EPS) {
			cout << i << endl;
			break;
		}
	}
}