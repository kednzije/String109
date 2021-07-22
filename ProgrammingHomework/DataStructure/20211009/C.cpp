#include <iostream>
using namespace std;
constexpr int MAXN = 5e5 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}

char s[MAXN * 2];
int d[MAXN * 2];

int main() {
	string str;
	cin >> str;
	int n = str.length();
	for(int i = 0; i < n; i++) {
		s[2 * i + 1] = str[i];
	}
	n = 2 * n + 1;
	int maxd= 0;
	for(int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
		while(0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
			k++;
		}
		d[i] = k--;
		if(i + k > r) {
			l = i - k;
			r = i + k;
		}
		if(0 == l) {
			maxd = max(maxd, 2 * k + 1);
		}
	}
	cout << (n - 1) / 2 - maxd / 2 << endl;
}