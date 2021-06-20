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

map <int, int> l, r, best, worst;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		l.clear(), r.clear(), best.clear(), worst.clear();
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

		for(int i = 2; i <= n; i++) {
			if(a[i].score + b[n - i + 2] > a[1].score + b[1]) {
				r[a[i].score + b[n - i + 2]]++;
			}
		}

		best[a[1].score] = 1;
		for(int i = 2; i <= n; i++) {
			if(a[i - 1].score + b[n - i + 1] > a[i].score + b[1]) {
				l[a[i - 1].score + b[n - i + 1]]++;
			}
			r[a[i].score + b[n - i + 2]]--;
			if(r[a[i].score + b[n - i + 2]] == 0) {
				r.erase(a[i].score + b[n - i + 2]);
			}

			best[a[i].score] = l.size() + r.size();
		}
	}
}