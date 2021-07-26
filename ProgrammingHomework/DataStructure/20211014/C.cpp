#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 10;

int n, num[MAXN], cnt[MAXN];
int get_flowers(int i) {
	if(i < 1 || i > n) {
		return 0;
	}
	if(!cnt[i]) {
		cnt[i] = max((num[i] > num[i - 1] ? get_flowers(i - 1) : 0), (num[i] > num[i + 1] ? get_flowers(i + 1) : 0)) + 1;
	}
	return cnt[i];
}

int main() {
	while(cin >> num[++n]);
	n--;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += get_flowers(i);
	}
	cout << sum << endl;
}