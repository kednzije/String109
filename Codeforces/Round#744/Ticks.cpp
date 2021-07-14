#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN = 25;

int n, m, k;
char field[MAXN][MAXN];
bool obtained[MAXN][MAXN];

inline bool check(int i, int j) {
	return i > 0 && i <= n && j > 0 && j <= m && field[i][j] == '*';
}
bool search(int x, int y, int d) {
	if(!check(x, y)) {
		return false;
	}
	for(int i = 1; i <= d; i++) {
		if(!check(x - i, y - i) || !check(x - i, y + i)) {
			return false;
		}
	}
	obtained[x][y] = true;
	for(int i = 1; i <= d; i++) {
		obtained[x - i][y - i] = obtained[x - i][y + i] = true;
	}
	return true;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(field, 0, sizeof(field));
		memset(obtained, false, sizeof(obtained));
		cin >> n >> m >> k;
		for(int i = 1; i <= n; i++) {
			cin >> field[i] + 1;
		}
		bool succ = true;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(field[i][j] == '*') {
					bool found = obtained[i][j];
					for(int d = k; d < n; d++) {
						if(!check(i + d, j + d)) {
							break;
						}
						if(search(i + d, j + d, d)) {
							found = true;
						}
					}
					succ &= found;
					if(!succ) {
						break;
					}
				}
			}
			if(!succ) {
				break;
			}
		}
		cout << (succ ? "Yes" : "No") << endl;
	}
}
/*
8
2 3 1
*.*
...
No
4 9 2
*.*.*...*
.*.*...*.
..*.*.*..
.....*...
Yes
4 4 1
*.*.
****
.**.
....
Yes
5 5 1
.....
*...*
.*.*.
..*.*
...*.
Yes
5 5 2
.....
*...*
.*.*.
..*.*
...*.
No
4 7 1
*.....*
.....*.
..*.*..
...*...
No
3 3 1
***
***
***
No
3 5 1
*...*
.***.
.**..
No
*/