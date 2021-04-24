#include <iostream>
#include <string>
#include <set>
using namespace std;

set <string> dir;

bool check(string s) {
	if(dir.count(s) || s.empty()) {
		return true;
	}
	int l = s.length();
	char c = 'a' + l - 1;
	string subs;
	if(s[0] == c) {
		subs = s.substr(1, l);
	}
	else if(s[l - 1] == c) {
		subs = s.substr(0, l - 1);
	}
	else {
		return false;
	}
	if(check(subs)) {
		dir.insert(s);
		return true;
	}
	return false;
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		string s;
		cin >> s;
		if(check(s)) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}