#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>
#include <cstdio>
using namespace std;
constexpr int MAXN = 1005;

pair <int, int> inter[MAXN];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) {
			scanf("%d%d", &inter[i].first, &inter[i].second);
			if(inter[i].second < inter[i].first) {
				inter[i].second += n;
			}
		}
		sort(inter + 1, inter + 1 + m);
	}
}