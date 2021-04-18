#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const double EPS = 1e-7;

inline bool equal(double a, double b) {
	return fabs(a - b) < EPS;
}

void dfs(double c, double m, double p, const double &v, double &ans, int races, double prob) {
	ans += races * prob * p;
	if(equal(p, 1)) {
		return;
	}
	if(equal(c, 0)) {
		if(m > v) {
			dfs(c, m - v, p + v, v, ans, races + 1, prob * m);
		}
		else {
			dfs(c, 0, p + m, v, ans, races + 1, prob * m);
		}
	}
	else if(equal(m, 0)) {
		if(c > v) {
			dfs(c - v, m, p + v, v, ans, races + 1, prob * c);
		}
		else {
			dfs(0, m, p + c, v, ans, races + 1, prob * c);
		}
	}
	else {
		if(m > v) {
			dfs(c + v / 2, m - v, p + v / 2, v, ans, races + 1, prob * m);
		}
		else {
			dfs(c + m / 2, 0, p + m / 2, v, ans, races + 1, prob * m);
		}
		if(c > v) {
			dfs(c - v, m + v / 2, p + v / 2, v, ans, races + 1, prob * c);
		}
		else {
			dfs(0, m + c / 2, p + c / 2, v, ans, races + 1, prob * c);
		}
	}
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		double c, m, p, v, ans = 0;
		cin >> c >> m >> p >> v;
		dfs(c, m, p, v, ans, 1, 1.0);
		cout << setprecision(12) << ans << endl;
	}
}