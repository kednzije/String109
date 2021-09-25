#include <iostream>
#include <list>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1e5 + 10;

list <int> sta[MAXN];
int len[MAXN];

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 1; i <= n; i++) {
			sta[i].clear();
			sta[i].push_back(i);
			len[i] = 1;
		}
		while(m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			sta[a].reverse();
			sta[b].splice(sta[b].end(), sta[a]);
			
			len[b] += len[a];
			len[a] = 0;
		}
		for(int i = 1; i <= n; i++) {
			printf("%d ", len[i]);
			for(auto elem: sta[i]) {
				printf("%d ", elem);
			}
			putchar('\n');
		}
	}
}