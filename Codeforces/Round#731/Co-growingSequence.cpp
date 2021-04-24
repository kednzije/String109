#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int x, y=0, n;
		scanf("%d%d", &n, &x);
		printf("0 ");
		for(int i = 1; i < n; i++) {
			int next;
			scanf("%d", &next);
			y = (~next) & (x ^ y);
			x = next;
			printf("%d ", y);
		}
		printf("\n");
	}
}