#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
constexpr int MAXN = 5e5 + 10;

set <int> broken_bits;

int main() {
	int n, cnt_changes, cnt_broken_bits;
	cin >> n >> cnt_changes >> cnt_broken_bits;
	for(int i = 1; i <= cnt_broken_bits; i++) {
		int broken_bit;
		cin >> broken_bit;
		broken_bits.insert(broken_bit);
	}
	int cnt_now_changes = 0, last_bit;
	if(1 == cnt_changes % 2) {
		cout << 1;
		cnt_now_changes++;

		last_bit = 1;
	}
	else {
		cout << 0;

		last_bit = 0;
	}
	for(int i = 2; i <= n; i++) {
		if(broken_bits.count(i) || cnt_now_changes == cnt_changes || 1 == last_bit) {
			cout << 0;
			last_bit = 0;
			continue;
		}
		cout << 1;
		cnt_now_changes += 2, last_bit = 1;
	}

	cout << endl;
}