#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
constexpr int MAXN = 1e5 + 10; // groups
constexpr int MAXM = 2e5 + 10; // students

set <int> groups[MAXN];
int n, m, s, cnt[MAXM], tag[MAXN];

void clear_tag(int i) {
	if(tag[i] == 0) {
		return;
	}
	for(auto x: groups[i]) {
		cnt[x] += tag[i];
	}
	tag[i] = 0;
}
void join_group(int x, int y) {
	// clear_tag(y);
	groups[y].insert(x);
	cnt[x] -= tag[y];
}
void leave_group(int x, int y) {
	// clear_tag(y);
	groups[y].erase(x);
	cnt[x] += tag[y];
}

int main() {
	scanf("%d%d%d", &n, &m, &s);
	while(s--) {
		static int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		switch (t) {
		case 1: {
			join_group(x, y);
			break;
		}
		case 2: {
			leave_group(x, y);
			break;
		}
		case 3: {
			cnt[x]--, tag[y]++;
			break;
		}

		default: {
			break;
		}
		}
	}
	for(int i = 1; i <= n; i++) {
		clear_tag(i);
	}
	for(int i = 1; i <= m; i++) {
		printf("%d\n", cnt[i]);
	}
}