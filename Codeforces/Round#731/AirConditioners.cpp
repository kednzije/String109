#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXSIZE = 3e5 + 7;
const int INF = 1e9 + 1e7;

struct Cond {
	int pos, temp;
	Cond() { pos = temp = 0; }
	Cond(int p, int t) {
		pos = p, temp = t;
	}
	bool operator < (const Cond& that) {
		return pos < that.pos;
	}
} conds[MAXSIZE];

int temp[MAXSIZE];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		memset(temp, 0, sizeof(temp));
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; i++) {
			scanf("%d", &conds[i].pos);
		}
		for(int i = 0; i < m; i++) {
			scanf("%d", &conds[i].temp);
		}
		sort(conds, conds + m);
		int minT = INF, ind=0;
		for(int i = 1; i <= n; i++) {
			if(ind < m && conds[ind].pos == i) {
				minT = min(minT, conds[ind].temp - conds[ind].pos);
				ind++;
			}
			temp[i] = minT + i;
		}
		minT = INF, ind = m - 1;
		for(int i = n; i >= 1; i--) {
			if(ind >= 0 && conds[ind].pos == i) {
				minT = min(minT, conds[ind].temp + conds[ind].pos);
				ind--;
			}
			temp[i] = min(temp[i], minT - i);
		}
		for(int i = 1; i <= n; i++) {
			printf("%d ", temp[i]);
		}
		printf("\n");
	}
}