#include <iostream>
#include <cstring>
using namespace std;
typedef unsigned long long ull;
const int MAXLEN = 1e5 + 5;

ull pos[MAXLEN], speed[MAXLEN];
ull n, k, x, p[MAXLEN], t[MAXLEN];

int main() {
	int ans = 0;
	cin >> n >> k >> x >> p[0];
	t[0] = 0;
	for(int i = 1; i <= n; i++) {
		cin >> speed[i];
	}
	for(int i = 1; i <= k; i++) {
		cin >> t[i];
	}
	for(int i = 1; i <= k; i++) {
		cin >> p[i];
	}
	memset(pos, 0, sizeof(pos));
	for(int i = 0; i < k; i++) {
		for(int j = 1; j <= n; j++) {
			if(pos[j] >= x) {
				continue;
			}
			if(pos[j] + speed[j] * (p[i] - t[i]) >= x) {
				pos[j] += speed[j] * (t[i + 1] - t[i]);
			}
			if(pos[j] >= x) {
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}