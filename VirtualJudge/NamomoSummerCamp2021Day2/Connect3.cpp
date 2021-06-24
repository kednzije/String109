#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
constexpr int MAXN = 10;
#define 	_NULL		0
#define 	WHITE 		1
#define 	BLACK 		2
#define 	OTHER		(3 - plyr)

int brd[MAXN][MAXN], a, b;

set <int> sta;

inline bool pos_check(int x, int y) {
	return x >= 1 && x <= 4 && y >= 1 && y <= 4;
}

constexpr int dir[4][2] = {
	0, 1,
	1, 0,
	1, 1,
	1, -1,
};
bool win_check(int plyr) {
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			if(brd[i][j] != plyr) {
				continue;
			}
			for(int d = 0; d < 4; d++) {
				for(int k = 0; k < 3; k++) {
					int x = i + dir[d][0] * k, y = j + dir[d][1] * k;
					if(!pos_check(x, y) || brd[x][y] != plyr) {
						break;
					}
					if(k == 2) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

inline int brd_hash() {
	int hash = 1;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 4; j++) {
			hash = hash * 3 + brd[i][j];
		}
	}
	return hash;
}

int ans=0;
void nxt_turn(int plyr, int last_pos_x, int last_pos_y) {
	if(win_check(WHITE)) {
		ans += (last_pos_x == a && last_pos_y == b);
		return;
	}
	if(win_check(BLACK) || (last_pos_x == a && last_pos_y == b)) {
		return;
	}

	for(int j = 1; j <= 4; j++) {
		int i;
		for(i = 1; i <= 4; i++) {
			if(brd[i][j] == _NULL) {
				break;
			}
		}
		if(!pos_check(i, j)) {
			continue;
		}
		brd[i][j] = plyr;
		int hash = brd_hash();
		if(sta.count(hash) > 0) {
			brd[i][j] = _NULL;
			continue;
		}
		sta.insert(hash);
		nxt_turn(OTHER, i, j);
		brd[i][j] = _NULL;
	}
}

int main() {
	memset(brd, _NULL, sizeof(brd));

	int x;
	cin >> x;
	brd[1][x] = BLACK;

	cin >> a >> b;
	nxt_turn(WHITE, 1, x);

	cout << ans << endl;
}