#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 10;

vector <int> sta[MAXN];
int from[MAXN];

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		memset(from, 0, sizeof(from));
		for(int i = 1; i <= n; i++) {
			sta[i].clear();
			sta[i].push_back(i);
			from[i] = i;
		}
		while(m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			// reverse(sta[a].begin(), sta[a].end());
			if(!sta[b].empty()) {
				sta[b].insert(sta[b].end(), sta[a].rbegin(), sta[a].rend());
				sta[a].clear();
				sta[a].shrink_to_fit();
			}
			else {
				from[b] = -from[a];
				from[a] = 0;
			}
		}
		for(int i = 1; i <= n; i++) {
			if(from[i] != 0) {
				vector <int> &sta_pre = sta[from[i] > 0 ? from[i] : -from[i]];
				printf("%d ", sta_pre.size());
				// for(auto elem: sta_pre) {
				// 	printf("%d ", elem);
				// }
				if(from[i] > 0) {
					for(int i = 0; i < sta_pre.size(); i++) {
						printf("%d ", sta_pre[i]);
					}
				}
				else {
					for(int i = sta_pre.size() - 1; i >= 0; i--) {
						printf("%d ", sta_pre[i]);	
					}
				}
			}
			else {
				printf("0");
			}
			printf("\n");
		}
	}
}
