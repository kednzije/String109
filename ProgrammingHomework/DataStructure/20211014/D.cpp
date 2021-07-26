#include <iostream>
using namespace std;
using ll = long long;

int main() {
	ll a, b, ans = 0, selector = 1;
	cin >> a >> b;
	for(int i = 0; i < 64; i++, selector <<= 1) {
		int cnt = 0;
		ll _a = a & (selector - 1), _b = b & (selector - 1), x, y;
		if((a >> i) & 1) {
			cnt += selector - _a;
			x = a - _a + selector;
		}
		else {
			x = a - _a;
		}
		if((b >> i) & 1) {
			cnt += _b + 1;
			y = b - _b - selector;
		}
		else {
			y = b - _b;
		}
		cnt += (y - x) / 2;

		ans |= (cnt % 2 ? selector : 0);
	}
	cout << ans << endl;
}