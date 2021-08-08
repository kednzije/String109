#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int T;
	cin >> T;

	string a, b;
	vector <int> diff;
	vector <char> ans;
	for(int ind = 1; ind <= T; ind++) {
		a.clear(), b.clear(), diff.clear();
		cin >> a >> b;
		ans = vector <char>(a.length());
		for(int i = 0; i < a.length(); i++) {
			if(a[i] == b[i]) {
				ans[i] = 'a';
			}
			else {
				diff.push_back(i);
			}
		}
		int cnta = 0, cntb = 0, x = diff.size();
		auto check = [=](int __cnta, int __cntb, int __pos, int __x) {
			__cnta += (a[diff[__pos]] == 'a'), __cntb += (b[diff[__pos]] == 'a');
			// if(__pos == 2) cout << __cnta << " " << __cntb << "??" << endl;
			if(abs(__cnta - __cntb) + 1 > (__x - __pos)) {
				return false;
			}
			return true;
		};
		for(int pos = 0; pos < diff.size(); pos++) {
			if(check(cnta, cntb, pos, x)) {
				//cout << diff[pos] << "??" << endl;
				ans[diff[pos]] = 'a';
				cnta += (a[diff[pos]] == 'a'), cntb += (b[diff[pos]] == 'a');
			}
			else {
				// cout << pos << " " << "QQQ" << endl;
				if(a[diff[pos]] != 'a' && b[diff[pos]] != 'a') {
					if(cnta > cntb) {
						for(int i = pos; i < diff.size(); i++) {
							ans[diff[i]] = b[diff[i]];
						}
						break;
					}
					if(cnta < cntb) {
						for(int i = pos; i < diff.size(); i++) {
							ans[diff[i]] = a[diff[i]];
						}
						break;
					}
				}
				else if(a[diff[pos]] == 'a') {
					bool flag = false;
					if(cnta - cntb == x - pos) {
						//cout << "qwq" << endl;
						for(int i = pos; i < diff.size(); i++) {
							ans[diff[i]] = b[diff[i]];
						}
						break;
					}
					// x-1
					for(int i = pos; i < diff.size(); i++) {
						if(i == diff.size() - 1) {
							//cout << "!!" << endl;
							for(char c  = 'a'; c <= 'z'; c++) {
								if(c != a[diff[i]] && c != b[diff[i]]) {
									ans[diff[i]] = c;
									break;
								}
							}
						}
						else {
							// cout << pos << "hhh" << endl;
							for(char c = 'a'; c < b[diff[i]]; c++) {
								// cout << c << " ?? " << a[diff[i]] << endl;
								if(c == a[diff[i]]) {
									continue;
								}
								flag = true;
								ans[diff[i]] = c;
								for(int j = pos + 1; j < diff.size(); j++) {
									ans[diff[j]] = b[diff[j]];
								}
								break;
							}
							if(flag) break;
							ans[diff[i]] = b[diff[i]];
							// cout << ans[diff[i]] << " " << i << "??s" << endl;
						}
						// cout << ans[diff[2]] << "!!!!!!" << endl;
					}
					break;
				}
				else {
					bool flag = false;
					if(cntb - cnta == x - pos) {
						for(int i = pos; i < diff.size(); i++) {
							ans[diff[i]] = a[diff[i]];
						}
						break;
					}
					// x-1
					for(int i = pos; i < diff.size(); i++) {
						if(i == diff.size() - 1) {
							for(char c = 'a'; c <= 'z'; c++) {
								if(c != a[diff[i]] && c != b[diff[i]]) {
									ans[diff[i]] = c;
									break;
								}
							}
						}
						else {
							for(char c = 'a'; c < a[diff[i]]; c++) {
								if(c == b[diff[i]]) {
									continue;
								}
								flag = true;
								ans[diff[i]] = c;
								for(int j = pos + 1; j < diff.size(); j++) {
									ans[diff[j]] = a[diff[j]];
								}
								break;
							}
							if(flag) break;
							ans[diff[i]] = a[diff[i]];
						}
					}
					break;
				}
			}
		}
		// cout << ans.size() << endl;
		cout << "Case " << ind << ": ";
		for(auto c: ans) {
			cout << c;
		}
		cout << endl;
	}
}
