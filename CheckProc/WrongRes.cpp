#include<iostream>
using namespace std;
int num[100000], stc[100000];
int main(void) {
	freopen("Data.in", "r", stdin);
    freopen("WrongRes.out", "w", stdout);
	int in, top = 0, cnt;
	for (cnt = 0; cin >> in; cnt++) {
		num[cnt] = in;
		while (top && num[stc[top - 1]] < in) num[stc[--top]] = cnt - stc[top];
		stc[top++] = cnt;
	}
	for (int b = 0; b < top; b++) num[stc[b]] = 0;
	for (int b = 0; b < cnt; b++) cout << " "[b == 0] << num[b];
	return 0;
}