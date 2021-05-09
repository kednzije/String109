#include <iostream>
#include <string>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, a, b;
		cin >> n >> a >> b;
		string s;
		cin >> s;
		int ans = 0;
		ans += a * s.length();
		if(b >= 0) {
			ans += b * s.length();
		}
		else {
			int cnt = 0;
			for(int i = 0; i < s.length(); i++) {
				if(!i || s[i] != s[i - 1]) {
					cnt++;
				}
			}
			ans += b * ((cnt + 2) / 2);
		}
		cout << ans << endl;
	}
}