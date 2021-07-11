#include <iostream>
using namespace std;

string s;
int getPoint(int l, int r) {
	if(l >= r) {
		return 0;
	}
	if(s[l] == '(' && s[r] == ')' && l + 1 == r) {
		return 1;
	}
	int sta = 0;
	for(int i = l; i <= r; i++) {
		if(s[i] == '(') {
			sta++;
		}
		if(s[i] == ')') {
			sta--;
		}
		if(sta == 0 && i != r) {
			return getPoint(l, i) + getPoint(i + 1, r);
		}
	}
	return 2 * getPoint(l + 1, r - 1);
}

int main() {
	int n;
	cin >> n >> s;
	cout << getPoint(0, n - 1) << endl;
}