#include <iostream>
#include <cmath>
using namespace std;

double f(double i) {
	return i * (i + 1) * (i + 1) * (i + 2) * pow(1.0 / 3, i + 1);
}

int main() {
	double ans = 0;
	for(int i = 1; i <= 100000; i++) {
		ans += f(i);
	}
	cout << ans << endl;
}