#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
constexpr int MAXN = 4e3 + 50;
constexpr int TO[4][2] = {
	0, 1,
	1, 0,
	0, -1,
	-1, 0
};
constexpr char FOORPRINT[2] = {
	'R', 'F'
};

char grass_map[MAXN][MAXN];
bool vis[MAXN][MAXN];

int main() {
	memset(grass_map, '.', sizeof(grass_map));

	int n, m, steps_cnt = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", grass_map[i] + 1);
		for(int j = 1; j <= m; j++) {
			steps_cnt += (grass_map[i][j] != '.');
		}
	}
	int steps_cnt_tmp = 0, ans = 0;
	queue <pair <int, int>> que;
	while(steps_cnt_tmp < steps_cnt) {
		ans++;
		while(!que.empty()) {
			que.pop();
		}
		memset(vis, false, sizeof(vis));
		que.push({ 1, 1 });
		vis[1][1] = true;
		steps_cnt_tmp = 1;
		grass_map[1][1] = FOORPRINT[grass_map[1][1] == FOORPRINT[0]];

		while(!que.empty()) {
			int x = que.front().first, y = que.front().second;
			que.pop();
			for(int i = 0; i < 4; i++) {
				int x_to = x + TO[i][0], y_to = y + TO[i][1];
				if(vis[x_to][y_to] || grass_map[x_to][y_to] == grass_map[x][y] || grass_map[x_to][y_to] == '.') {
					continue;
				}
				que.push({ x_to, y_to });
				vis[x_to][y_to] = true;
				steps_cnt_tmp++;

				grass_map[x_to][y_to] = FOORPRINT[grass_map[x_to][y_to] == FOORPRINT[0]];
			}
		}
	}
	printf("%d\n", ans);
}