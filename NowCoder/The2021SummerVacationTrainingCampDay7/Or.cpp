#include <iostream>
using namespace std;

int main() {
	int x, s;
	cin >> x >> s;
	int ans = 1;
	for(int i = 1; i <= 31; i++, x >>= 1, s >>= 1) {
		if(x & 1 && s & 1) {
			ans <<= 1;
		}
		if(x & 1 && !(s & 1)) {
			ans = 0;
			break;
		}
	}
	cout << ans << endl;
}