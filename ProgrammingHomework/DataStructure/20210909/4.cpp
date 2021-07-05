#include <iostream>
using namespace std;
constexpr int MAXN = 1e5 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}

int sum[MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	int mini = 0, ans = INT_MIN;
	for(int i = 1; i <= n; i++) {
		ans = max(sum[i] - sum[mini], ans);

		if(sum[i] < sum[mini]) {
			mini = i;
		}
	}
	cout << ans << endl;
}