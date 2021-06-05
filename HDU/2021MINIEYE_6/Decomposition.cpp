#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 1005;

int n;
bool used[MAXN][MAXN];
map <int, vector <int>> euler;
vector <int> euler_path;

void dfs(int pos) {
	for(int i = 1; i <= n; i++) {
		if(used[pos][i]) {
			continue;
		}
		used[pos][i] = used[i][pos] = true;
		dfs(i);
	}
	euler_path.push_back(pos);
}

void find_euler() {
	memset(used, false, sizeof(used));
	for(int i = 1; i <= n; i++) {
		used[i][i] = true;
	}
	euler_path.clear();
	dfs(1);
	euler[n] = euler_path;
}

int main() {
	int t;
	scanf("%d", &t);
	for(int case_ind = 1; case_ind <= t; case_ind++) {
		int k;
		scanf("%d%d", &n, &k);
		if(!euler.count(n)) {
			find_euler();
		}
		vector <int> &path = euler[n];
		for(auto node: path) {
			printf("%d ", node);
		}
		printf("\n");
		int cnt = 0, l;
		printf("Case #%d:\n", case_ind);
		for(int i = 1; i <= k; i++) {
			scanf("%d", &l);
			for(int j = 0; j <= l; j++) {
				printf("%d", path[cnt + j]);
				if(j < l) {
					printf(" ");
				}
				else {
					printf("\n");
				}
			}
			cnt += l;
		}
	}
}