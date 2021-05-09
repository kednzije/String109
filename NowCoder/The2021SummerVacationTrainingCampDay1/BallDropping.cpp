#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
	double r, a, b, h;
	cin >> r >> a >> b >> h;
	if(b >= 2 * r) {
		cout << "Drop" << endl;
		return 0;
	}
	double tanX = (a - b) / (2 * h);
	double ans = r / sqrt(tanX * tanX / (tanX * tanX + 1)) - b / (2 * tanX);
	cout << "Stuck" << endl;
	// cout << setprecision(11) << ans << endl;
	printf("%.10lf\n", ans);
}