#include <iostream>
using namespace std;

int dis[2], ans[4];

int main() {
	cout << "? 1 1" << endl;
	cout.flush();
	cin >> dis[0];
	cout << "? 1000000000 1" << endl;
	cout.flush();
	cin >> dis[1];
	cout << "? " << (1000000000 + 1 + dis[0] - dis[1]) / 2 << " 1" << endl;
	// cout << (1e9 + 1 + dis[0] - dis[1]) << endl;
	cout.flush();
	cin >> ans[1]; // y
	ans[1]++;
	ans[0] = 2 + dis[0] - ans[1];
	// cout << ans[0] << ' ' << ans[1];
	cout << "? 1 1000000000" << endl;
	cout.flush();
	cin >> dis[0];
	cout << "? 1000000000 1000000000" << endl;
	cout.flush();
	cin >> dis[1];
	cout << "? " << (1000000000 + 1 + dis[0] - dis[1]) / 2 << " 1000000000" << endl;
	cout.flush();
	cin >> ans[3];
	ans[3] = 1e9 - ans[3];
	ans[2] = 2e9 - dis[1] - ans[3];
	cout << "! ";
	for(int i = 0; i < 4; i++) {
		cout << ans[i] << ' ';
	}
	cout << endl;
	cout.flush();
}