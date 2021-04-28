#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
using namespace std;

unordered_map <string, char> dir;
void makeDir() {
	for(char c = 'a'; c <= 'z'; c++) {
		string s;
		s.push_back(c);
		dir[s] = c;
	}
	dir["iu"] = 'q';
	dir["ei"] = 'w';
	dir["uan"] = 'r';
	dir["ue"] = 't';
	dir["un"] = 'y';
	dir["sh"] = 'u';
	dir["ch"] = 'i';
	dir["uo"] = 'o';
	dir["ie"] = 'p';
	dir["ong"] = 's';
	dir["iong"] = 's';
	dir["ai"] = 'd';
	dir["en"] = 'f';
	dir["eng"] = 'g';
	dir["ang"] = 'h';
	dir["an"] = 'j';
	dir["uai"] = 'k';
	dir["ing"] = 'k';
	dir["uang"] = 'l';
	dir["iang"] = 'l';
	dir["ou"] = 'z';
	dir["ia"] = 'x';
	dir["ua"] = 'x';
	dir["ao"] = 'c';
	dir["zh"] = 'v';
	dir["ui"] = 'v';
	dir["in"] = 'b';
	dir["iao"] = 'n';
	dir["ian"] = 'm';
}

int main() {
	makeDir();
	string str;
	while(getline(cin, str)) {
		string ans;
		regex reg(" ");
		sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
		decltype(pos) end;
		for(; pos != end; ++pos) {
			const string &token = pos->str();
			if(token.length() == 2) {
				ans = ans + token + ' ';
			}
			else if(dir.count(token)) {
				ans = ans + token[0] + dir[token] + ' ';
			}
			else {
				int i=0;
				for(; i < token.length(); i++) {
					if(token[i] == 'a'
						|| token[i] == 'o'
						|| token[i] == 'e'
						|| token[i] == 'i'
						|| token[i] == 'u'
						|| token[i] == 'v') {
						break;
					}
				}
				ans = ans + dir[token.substr(0, i)] + dir[token.substr(i, token.length())] + ' ';
			}
		}
		cout << ans << endl;
	}
}