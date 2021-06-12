#include <iostream>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int n, b[MAXN], c[MAXN];

int main() {
	cin >> n;
	for(int i = 2; i <= n; i++) {
		cin >> b[i];
	}
	for(int i = 2; i <= n; i++) {
		cin >> c[i];
		c[i] -= b[i];
	}
	// b[i] = a[i-1] | a[i]
	// c[i] = a[i-1] & a[i]
	int ans = 1;
	auto check = [=](int bit) {
		for(int i = 2; i <= n; i++) {
			int nxt_bit;
			if(bit) {
				nxt_bit = c[i] & 1;
				if((bit | nxt_bit) != (b[i] & 1)) {
					return false;
				}
			}
			else {
				nxt_bit = b[i] & 1;
				if((bit & nxt_bit) != (c[i] & 1)) {
					return false;
				}
			}
			bit = nxt_bit;
		}
		return true;
	};
	for(int k = 1; k <= 30; k++) {
		int cnt = check(0) + check(1);
		ans *= cnt;
		if(ans == 0) {
			break;
		}
		for(int i = 2; i <= n; i++) {
			b[i] >>= 1, c[i] >>= 1;
		}
	}
	cout << ans;
}