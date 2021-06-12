#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
constexpr int MAXN = 505;

char mapp[MAXN][MAXN];
int color[MAXN][MAXN];
int to[2][2] = {
	1, 0,
	0, 1,
};

void init(int n, int m) {
	queue <pair <int, int>> que;
	int clr = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(mapp[i][j] == '1' || color[i][j] != 0) {
				continue;
			}
			color[i][j] = ++clr;
			que.push(make_pair(i, j));
			while(!que.empty()) {
				pair <int, int> pos = que.front();
				que.pop();
				for(int k = 0; k < 2; k++) {
					pair <int, int> nxt_pos = pos;
					nxt_pos.first += to[k][0], nxt_pos.second += to[k][1];
					if(nxt_pos.first > n || nxt_pos.second > n
						|| mapp[nxt_pos.first][nxt_pos.second] == '1') {
						continue;
					}
					color[nxt_pos.first][nxt_pos.second] = color[pos.first][pos.second];
					que.push(nxt_pos);
				}
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		// cin >> (mapp[i] + 1);
		scanf("%s", mapp[i] + 1);
	}
	init(n, m);
	int t;
	scanf("%d", &t);
	int type, frm_x, frm_y, to_x, to_y;
	while(t--) {
		// cin >> type;
		scanf("%d", &type);
		// cin >> frm_x >> frm_y >> to_x >> to_y;
		scanf("%d%d%d%d", &frm_x, &frm_y, &to_x, &to_y);
		switch (type)
		{
		case 1:
			if(frm_y == to_y && color[frm_x][frm_y] == color[to_x][to_y]) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		case 2:
			if(frm_x == to_x && color[frm_x][frm_y] == color[to_x][to_y]) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		case 3:
			if(color[frm_x][frm_y] == color[to_x][to_y]) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		
		default:
			break;
		}
	}
}