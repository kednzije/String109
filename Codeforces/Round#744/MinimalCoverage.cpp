#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 1e4 + 10;
inline int min(int a, int b) {
	return a < b ? a : b;
}
inline int max(int a, int b) {
	return a > b ? a : b;
}

int n, ans, lens[MAXN];

void dfs(int i, int l, int r, int pos) {
	if(i >= n || r - l >= ans) {
		ans = min(ans, r - l);
		return;
	}
	if(rand() % 2) {
		dfs(i + 1, l, max(r, pos + lens[i + 1]), pos + lens[i + 1]);
		dfs(i + 1, min(l, pos - lens[i + 1]), r, pos - lens[i + 1]);
	}
	else {
		dfs(i + 1, min(l, pos - lens[i + 1]), r, pos - lens[i + 1]);
		dfs(i + 1, l, max(r, pos + lens[i + 1]), pos + lens[i + 1]);
	}
}

int main() {
	srand(time(NULL));
	int t;
	cin >> t;
	while(t--) {
		ans = 0;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> lens[i];
			ans += lens[i];
		}
		dfs(1, 0, lens[1], lens[1]);
		cout << ans << endl;
	}
}