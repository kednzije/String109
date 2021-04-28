#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector <string> strs;

int main() {
	int t;
	cin >> t;
	while(t--) {
		strs.clear();
		int n, m;
		cin >> n >> m;
		for(int i = 1; i < 2 * n; i++) {
			string s;
			cin >> s;
			strs.emplace_back(s);
		}
		string stolen;
		for(int i = 0; i < m; i++) {
			char c = 0;
			for(auto &str: strs) {
				c ^= str[i];
			}
			stolen.push_back(c);
		}
		cout << stolen << endl;
	}
}