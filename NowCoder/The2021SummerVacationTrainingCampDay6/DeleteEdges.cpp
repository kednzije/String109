#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
constexpr int MAXN = 2005;

bool del[MAXN][MAXN];
int ans[MAXN * MAXN][3];

int main() {
	freopen("ans.txt", "w", stdout);
	time_t startTime = clock();
	int n;
	scanf("%d", &n);
	int edges = (n * (n - 1)) / 2, cnt = 0;
	
	for(int i = 1; i <= n && edges >= n; i++) {
		for(int j = i + 1; j <= n && edges >= n; j++) {
			if(del[i][j]) {
				continue;
			}
			for(int k = j + 1; k <= n && edges >= n; k++) {
				if(del[i][k] || del[j][k]) {
					continue;
				}
				cnt++, edges -= 3;
				del[i][j] = del[j][k] = del[i][k] = true;
				ans[cnt][0] = i, ans[cnt][1] = j, ans[cnt][2] = k;
				break;
			}
		}
	}

	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++) {
		printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	}
	time_t endTime = clock();
	printf("The run time is: %lfs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}