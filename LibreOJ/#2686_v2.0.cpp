// O1

#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
constexpr int MAXN = 4e3 + 50;
constexpr int TO[4][2] = {
	1, 0,
	0, 1,
	-1, 0,
	0, -1
};
constexpr char FOOTPRINT[2] = {
	'F', 'R'
};

int n, m;
char grass_map[MAXN][MAXN];
bool vis[MAXN][MAXN];

queue <pair <int, int>> que[2];

void bfs(bool which_animal) {
	queue <pair <int, int>> &this_que = que[which_animal], &that_que = que[!which_animal];
	while(!que[which_animal].empty()) {
		int x = this_que.front().first, y = this_que.front().second;
		this_que.pop();
		if(vis[x][y]) {
			continue;
		}
		vis[x][y] = true;
		for(int i = 0; i < 4; i++) {
			int x_to = x + TO[i][0], y_to = y + TO[i][1];
			if(vis[x_to][y_to]) {
				continue;
			}
			if(grass_map[x_to][y_to] == FOOTPRINT[which_animal]) {
				this_que.push({ x_to, y_to });
			}
			if(grass_map[x_to][y_to] == FOOTPRINT[!which_animal]) {
				that_que.push({ x_to, y_to });
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", grass_map[i] + 1);
	}
	bool which_animal = (grass_map[1][1] == FOOTPRINT[1]);
	que[which_animal].push({ 1, 1 });
	int ans = 0;
	while(!que[which_animal].empty()) {
		bfs(which_animal);
		which_animal = !which_animal;
		ans++;
	}
	printf("%d\n", ans);
}