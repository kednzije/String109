#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int MAXLEN = 1e5 + 5;

ull pos[MAXLEN], speed[MAXLEN];
ull n, k, x, p[MAXLEN], t[MAXLEN], len[MAXLEN];

int main() {
	int ans = 0;
	cin >> n >> k >> x >> p[0];
	for(int i = 1; i <= n; i++) {
		cin >> speed[i];
	}
	t[0] = 0;
	for(int i = 1; i <= k; i++) {
		cin >> t[i];
	}
	for(int i = 1; i <= k; i++) {
		cin >> p[i];
	}
	for(int i = 0; i <= k; i++) {
		len[i] = p[i] - t[i];
	}
	sort(len, len + 1 + k);
	int maxTime = len[k];
	for(int i = 1; i <= n; i++) {
		if(maxTime * speed[i] >= x) {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}