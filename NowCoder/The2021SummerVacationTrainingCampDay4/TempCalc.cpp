#include <iostream>
#include <cmath>
using namespace std;

double f(double i) {
	return i * (i + 1) * (i + 1) * (i + 2) * pow(1.0 / 3, i + 1);
}

double f(double k, double a) {
	return pow(1.0 / 2, 2 * k - a) * (k + 1) * (k + 1) * (3.0 / 4 * (k - a) + 0.5);
}

int main() {
	double ans = 0;
	for(int k = 1; k <= 20000; k++) {
		for(int a = 0; a < k; a++) {
			ans += f(k, a);
		}
	}
	cout << ans << endl;
}