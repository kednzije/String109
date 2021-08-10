#include <iostream>
using namespace std;
constexpr int MAXN = 1e4 + 10;
inline int max(int a, int b) {
	return a > b ? a : b;
}

bool vis[MAXN];

int n, pos[MAXN][2], color[MAXN];

int dfs(int ind, int len, int &pos_far) {
	vis[ind] = true, pos_far = ind;
	int maxlen = len, pos_far_tmp = ind;
	for(int i = 1; i <= n; i++) {
		if(!vis[i] && (pos[i][0] == pos[ind][0] || pos[i][1] == pos[ind][1])) {
			int l = dfs(i, len + 1, pos_far_tmp);
			if(l > maxlen) {
				maxlen = l, pos_far = pos_far_tmp;
			}
		}
	}
	vis[ind] = false;
	return maxlen;
}
void paint(int ind, int c) {
	color[ind] = c;
	for(int i = 1; i <= n; i++) {
		if(color[i] == 0 && (pos[i][0] == pos[ind][0] || pos[i][1] == pos[ind][1])) {
			paint(i, c);
		}
	}
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> pos[i][0] >> pos[i][1];
	}
	for(int i = 1; i <= n; i++) {
		if(color[i] == 0) {
			paint(i, i);
		}
	}
	int start, end, ans = 0;
	// ans = dfs(1, 1, start);
	// ans = dfs(start, 1, end);
	for(int i = 1; i <= n; i++) {
		if(color[i] == i) {
			ans = max(ans, dfs(i, 1, start));
			ans = max(ans, dfs(start, 1, end));
		}
	}
	cout << ans - 1 << endl;
}