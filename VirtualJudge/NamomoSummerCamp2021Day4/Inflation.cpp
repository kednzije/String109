#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 10;

int gas[MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> gas[i];
	}
	sort(gas + 1, gas + 1 + n);
	double ans = 1;
	for(int i = 1; i <= n; i++) {
		ans = min(ans, gas[i] > i ? -1 : 1.0 * gas[i] / i);
	}
	cout << ans << endl;
}