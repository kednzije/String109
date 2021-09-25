#include <iostream>
#include <cstdio>
using namespace std;

int sign_ext(int num, int len) {
	return (num & (0xffffffff >> (32 - len))) | (((num >> (len - 1)) & 1) ? (0xffffffff << len) : 0);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", sign_ext((a & (0x7ff)) + (b & 0x7ff), 11));
	}
}