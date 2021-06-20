#include <iostream>
#include <cstdio>
#include <utility>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
constexpr int MAXN = 5005;

#define score	first
#define index	second

pair <int, int> a[MAXN];
int b[MAXN];

map <int, int> l, r, bests, worsts;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		l.clear(), r.clear(), bests.clear(), worsts.clear();
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));

		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i].score);
			a[i].index = i;
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &b[i]);
		}

		sort(a + 1, a + 1 + n,
			[](const pair <int, int> &_a, const pair <int, int> &_b) { return _a.score > _b.score; });

		for(int i = 1; i <= n; i++) {
			if(i > 1 && a[i - 1].score + b[n - i + 1] > a[i].score + b[1]) {
				l[a[i - 1].score + b[n - i + 1]]++;
			}
			
			r.clear();
			for(int j = i + 1; j <= n; j++) {
				if(a[j].score + b[n - j + 2] > a[i].score + b[1]) {
					r[a[j].score + b[n - j + 2]]++;
				}
			}

			bests[a[i].score] = l.size() + r.size() + 1;
		}

		l.clear();
		for(int i = 1; i <= n; i++) {
			if(i > 1 && a[i - 1].score + b[n - i + 1] > a[i].score + b[n]) {
				l[a[i - 1].score + b[n - i + 1]]++;
			}
			
			r.clear();
			for(int j = i + 1; j <= n; j++) {
				if(a[j].score + b[n - j] > a[i].score + b[n]) {
					r[a[j].score + b[n - j]]++;
				}
			}

			worsts[a[i].score] = l.size() + r.size() + 1;
		}

		sort(a + 1, a + 1 + n,
			[](const pair <int, int> &_a, const pair <int, int> &_b) { return _a.index < _b.index; });

		for(int i = 1; i <= n; i++) {
			printf("%d %d\n", bests[a[i].score], worsts[a[i].score]);
		}
	}
}