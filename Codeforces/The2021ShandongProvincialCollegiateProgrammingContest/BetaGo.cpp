#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
const int MAXSIZE = 2e5 + 5;

int ver[MAXSIZE], hor[MAXSIZE];

void init() {
	memset(ver, 0, sizeof(ver));
	memset(hor, 0, sizeof(hor));
}

int main() {
	int n;
	scanf("%d", &n);
	init();
	int verl=0, horl=0, cnt=0;
	while(n--) {
		int x, y;
		scanf("%d%d", &x, &y);
		cnt = (ver[x - 1] > ver[x]) + (ver[x + 1] > ver[x]);
		switch(cnt) {
		case 2:
			if(ver[x]) {
				verl -= 2;
			}
			break;
		case 1:
			if(!ver[x]) {
				verl += 2;
			}
			break;
		case 0:
			if(ver[x]) {
				verl += 2;
			}
			else {
				verl += 4;
			}
			break;
		default:
			break;
		}

		cnt = (hor[y - 1] > hor[y]) + (hor[y + 1] > hor[y]);
		switch(cnt) {
		case 2:
			if(hor[y]) {
				horl -= 2;
			}
			break;
		case 1:
			if(!hor[y]) {
				horl += 2;
			}
			break;
		case 0:
			if(hor[y]) {
				horl += 2;
			}
			else {
				horl += 4;
			}
			break;
		default:
			break;
		}
		
		ver[x]++, hor[y]++;
		printf("%d %d\n", verl, horl);
	}
}