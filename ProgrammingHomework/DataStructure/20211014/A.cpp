#include <iostream>
#include <cstring>
using namespace std;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}
constexpr int MAXN = 1e3 + 10;

int cnt[MAXN];

int main() {
	memset(cnt, 0, sizeof(cnt));
	int n;
	while(cin >> n) {
		cnt[n]++;
	}
	int sum = 0;
	for(int i = 0; i < MAXN; i++) {
		sum += (cnt[i] == 1 ? i : 0);
	}
	cout << sum;
}