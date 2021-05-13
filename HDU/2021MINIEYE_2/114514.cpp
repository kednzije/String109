#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	string s;
	while(t--) {
		cin >> s;
		if(s.find("114514") != string::npos) {
			cout << "AAAAAA" << endl;
		}
		else {
			cout << "Abuchulaile" << endl;
		}
	}
}