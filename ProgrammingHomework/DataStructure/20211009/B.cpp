#include <iostream>
using namespace std;
constexpr int MAXN = 60;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}

int maxX[MAXN], maxY[MAXN], buildings[MAXN][MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> buildings[i][j];
			maxX[i] = max(maxX[i], buildings[i][j]);
			maxY[j] = max(maxY[j], buildings[i][j]);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			ans += min(maxX[i], maxY[j]) - buildings[i][j];
		}
	}
	cout << ans << endl;
}