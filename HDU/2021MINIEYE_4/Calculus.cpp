#include <iostream>
#include <string>
#include <regex>
#include <cstdio>
using namespace std;

inline bool isNum(char c) {
	return c >= '0' && c <= '9';
}

bool convergent(string& s) {
	static regex reg("[+]");
	sregex_token_iterator pos(s.begin(), s.end(), reg, -1);
	decltype(pos) end;

	bool conv = true;
	int num, i;

	for(; pos != end; pos++) {
		num = 0;
		for(i = 0; isNum(pos->str()[i]); i++) {
			num = num * 10 + (pos->str()[i] - '0');
		}
		if(num != 0) {
			conv = false;
			break;
		}
	}
	return conv;
}

int main() {
	int t;
	cin >> t;
	string s;
	while(t--) {
		cin >> s;
		if(convergent(s)) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
}