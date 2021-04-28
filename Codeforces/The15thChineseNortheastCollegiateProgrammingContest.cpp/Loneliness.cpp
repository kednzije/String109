#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

int n=100;
// struct Node {
// 	int x, y, val;
// 	int f() const {
// 		return n - x + n - y + val;
// 	}
// 	bool operator < (const Node that) {
// 		return f() > that.f();
// 	}
// };

// vector <pair <int, int>> input;
// bool getAns(string &ans) {
// 	string s;
	
// }

// int main() {
// 	int t;
// 	cin >> t >> n;
// 	for(int i = 1; i <= t; i++) {
// 		int k;
// 		cin >> k;
// 		input.emplace_back(k, i);
// 	}
// 	sort(input.begin(), input.end());
// 	string ans;
// 	int minK = INT_MAX;
// 	for(int i = 0; i < input.size(); i++) {
// 		minK = input[i].first;
// 		if(getAns(ans)) {
// 			break;
// 		}
// 	}
// 	sort(input.begin(), input.end(), 
// 		[](const pair <int, int> a, const pair <int, int> b) { return a.second < b.second; });
// 	for(int i = 0; i < input.size(); i++) {
// 		if(input[i].first < minK) {
// 			cout << -1 << endl;
// 		}
// 		else {
// 			cout << ans << endl;
// 		}
// 	}
// }


int loneliness[102][102];
int to[4][2] = {
	1, 0,
	-1, 0,
	0, 1,
	0, -1
};
char cto[] = { 'D', 'U', 'R', 'L' };
int add(int i, int v) {
	switch (i)
	{
	case 0:
		return v * 2;
	case 1:
		return v / 2;
	case 2:
		return v + 2;
	case 3:
		return v - 2;
	default:
		return 0;
	}
}
int maxK = 0;
void dfs(int x, int y, int val, int step, int k) {
	if(x == n && y == n) {
		loneliness[x][y] = min(loneliness[x][y], val);
		k = max(k, maxK);
		return;
	}
	if(step == 1000) {
		return;
	}
	for(int i = 0; i < 4; i++) {
		int xto = x + to[i][0], yto = y + to[i][1];
		if(i == 1 && val % 2) { continue; }
		if(i == 3 && val < 2) { continue; }
		if(loneliness[xto][yto] > add(i, val)) {
			loneliness[xto][yto] = add(i, val);
			dfs(xto, yto, add(i, val), step + 1, max(k, add(i, val)));
		}
	}
}
int main() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			loneliness[i][j] = INT_MAX;
		}
	}
	loneliness[1][1] = 1;
	dfs(1, 1, 1, 0, 1);
	cout << maxK << endl;
}