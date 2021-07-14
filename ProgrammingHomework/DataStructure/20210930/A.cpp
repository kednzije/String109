#include <iostream>
#include <string>
using namespace std;
#define toInd(c) (c == 0 ? 0 : c - 'a' + 1)
constexpr int MAXN = 2e6 + 10;

int sum[50];
char sta[MAXN];
bool insta[50];

int main() {
	string s;
	cin >> s;
	for(int i = 0; i < s.length(); i++) {
		sum[toInd(s[i])]++;
	}
	int size = 0;
	for(int i = 0; i < s.length(); i++) {
		sum[toInd(s[i])]--;
		if(insta[toInd(s[i])]) {
			continue;
		}
		while(sta[size] >= s[i] && sum[toInd(sta[size])]) {
			insta[toInd(sta[size])] = false;
			size--;
		}
		sta[++size] = s[i];
		insta[toInd(s[i])] = true;
	}
	for(int i = 1; i <= size; i++) {
		cout << sta[i];
	}
}