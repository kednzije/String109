#include <cstring>
#include <string>
using namespace std;

int Sunday(const string &haystack, const string &needle) {
	static int pos[256], len;
	memset(pos, -1, sizeof(pos));
	len = needle.length();
	for(int i = 0; i < len; i++) {
		pos[needle[i]] = i;
	}
	int now_pos = 0;
	for(int i = 0; i < haystack.length(); i++) {
		if(haystack[i] == needle[now_pos]) {
			now_pos++;
			if(now_pos >= len) {
				return i - len + 1;
			}
		}
		else {
			if(pos[haystack[i + len - now_pos]] == -1) {
				i += len - now_pos, now_pos = 0;
			}
			else {
				i += len - pos[haystack[i + len - now_pos]] - 1, now_pos = 0;
			}
		}
	}
	return haystack.length();
}
int Strstr(const string &haystack, const string &needle) {
	return Sunday(haystack, needle);
}

#include <iostream>
int main() {
	string s, p;
	getline(cin, s), getline(cin, p);
	cout << Strstr(s, p) << endl;

}