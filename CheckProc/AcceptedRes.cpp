#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e4 + 10;

int n, atk[MAXN];
bool alive[MAXN];

int main() {
	freopen("Data.in", "r", stdin);
    freopen("AcceptedRes.out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> atk[i];
	}
	memset(alive, true, sizeof(alive));

	for(int i = 1; i <= n; i++) {
		int dir = (atk[i] > 0 ? 1 : -1), atkmin = atk[i], atkmax = atk[i];
		for(int j = i + dir; j >= 1 && j <= n; j += dir) {
			atkmax = max(atkmax, atk[j]);
			atkmin = min(atkmin, atk[j]);
			if(atk[i] * (atkmax + atkmin) <= 0) {
				alive[i] = false;
				break;
			}
		}
	}

	for(int i = 1; i <= n; i++) {
		if(alive[i]) {
			cout << atk[i] << ' ';
		}
	}
	cout << endl;
}