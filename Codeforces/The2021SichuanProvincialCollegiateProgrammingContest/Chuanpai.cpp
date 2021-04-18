#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int k;
		cin >> k;
		int ans = 0;
		for(int i = 1; i <= 6; i++) {
			for(int j = i; j <= 6; j++) {
				if(i + j == k) {
					ans++;
				}
			}
		}
		cout << ans << endl;
	}
}