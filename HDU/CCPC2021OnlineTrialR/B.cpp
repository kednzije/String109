#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
#define EPS (1e-9)

double a, b, c, x[3], y[3];
double f(double x) {
	return a * x * x + b * x + c;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		cin >> a >> b >> c;
		cin >> x[0] >> x[1] >> y[0] >> y[1] >> y[2];
		x[2] = 2 * x[1] - x[0];
		// cout << f(x[0]) << ' ' << f(x[1]) << ' ' << f(x[2]) << endl;
		bool flag = false;
		if(fabs(f(x[1]) - y[0]) < EPS) {}
		else if(f(x[1]) < y[0]) {
			flag = (f(x[0]) > y[0]);
		}
		else {
			flag = (f(x[1]) <= y[2] && f(x[2]) < y[0]);
		}

		if(f(x[0]) <= y[0] && f(x[1]) >= y[0]) {
			flag = false;
		}
		cout << (flag ? "Yes" : "No") << endl;
	}
}