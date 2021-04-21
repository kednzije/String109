#include <iostream>
#include <regex>
#include <string>
using namespace std;

string trans(string s) {
	if(s == "ikimasu") {
		return string("itte");
	}
	regex reg0("imasu$"), reg1("chimasu$"), reg2("rimasu$"); // to "tte"
	regex reg3("mimasu$"), reg4("bimasu$"), reg5("nimasu$"); // to "nde"
	regex reg6("kimasu$"); // to "ite"
	regex reg7("gimasu$"); // to "ide"
	regex reg8("shimasu$"); // to "shite"
	string res;
	res = regex_replace(s, reg1, "tte");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg2, "tte");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg3, "nde");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg4, "nde");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg5, "nde");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg6, "ite");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg7, "ide");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg8, "shite");
	if(res != s) {
		return res;
	}
	res = regex_replace(s, reg0, "tte");
	return res;
}

int main() {
	int n;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		cout << trans(s) << endl;
	}
}