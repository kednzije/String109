#include <iostream>
#include <string>
using namespace std;

int main() {
	long long k;
	string str;
	cin >> k >> str;
	long long s = 0;
	for(int i = 0; i < str.length(); i++) {
		s = (s << 1) + (str[i] == '1');
	}
	int pos = 0;
	for(int i = 0; i <= 60; i++) {
		if((s >> i) & 1) {
			pos = i;
		}
	}
	int cnt = 0;
	pos--;
	while(s > k) {
		if(pos >= 0) {
			if(0ll == ((s >> pos) & 1ll)) {
				pos--;
				continue;
			}
			s = ((s >> (pos + 1)) << pos) + (s % (1ll << pos));
			pos--;
		}
		else {
			s >>= 1;
		}
		cnt++;
	}
	cout << cnt << endl;
}