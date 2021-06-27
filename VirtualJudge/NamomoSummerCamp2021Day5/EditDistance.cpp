#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	int l;
	cin >> s;
	l = s.length();
	int cnt0 = 0, cnt1 = 0;
	for(int i = 0; i < l; i++) {
		cnt0 += (s[i] == '0');
		cnt1 += (s[i] == '1');
	}
	if(cnt0 > cnt1 || cnt0 < cnt1) {
		char c = (cnt0 > cnt1 ? '1' : '0');
		for(int i = 1; i <= l; i++) {
			cout << c;
		}
		cout << endl;
		return 0;
	}
	if(s[0] == '0') {
		cout << '1';
		for(int i = 2; i <= l; i++) {
			cout << '0';
		}
	}
	else {
		cout << '0';
		for(int i = 2; i <= l; i++) {
			cout << '1';
		}
	}
	cout << endl;
	return 0;
}