#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, num;
		bool alice_win=false;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &num);
			alice_win ^= bool(num > 1);
		}
		if(alice_win) {
			printf("Alice\n");
		}
		else {
			printf("Bob\n");
		}
	}
}