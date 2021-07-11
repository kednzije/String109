#include <iostream>
using namespace std;
constexpr int MAXN = 1e4 + 10;

int sta[MAXN], stasz;

int main() {
	int n;
	cin >> n;

	stasz = 0;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		if(0 == stasz) {
			sta[++stasz] = x;
			continue;
		}
		while(stasz != 0) {
			if(sta[stasz] * x > 0 || x > 0) {
				sta[++stasz] = x;
				break;
			}
			else if(sta[stasz] + x < 0) {
				stasz--;
				if(0 == stasz) {
					sta[++stasz] = x;
					break;
				}
			}
			else if(sta[stasz] + x > 0) {
				break;
			}
			else {
				stasz--;
				break;
			}
		}
	}
	for(int i = 1; i <= stasz; i++) {
		cout << sta[i] << ' ';
	}
	cout << endl;
}