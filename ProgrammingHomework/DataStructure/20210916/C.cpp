#include <iostream>
using namespace std;
constexpr int MAXN = 1e5 + 10;
using ll = long long;

ll target, sum[MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	cin >> target;

	int l = 1, r = 1, minlen = -1;
	while(l <= n && r <= n) {
		if(sum[r] - sum[l - 1] >= target) {
			minlen = (minlen == -1 ? (r - l + 1) : (minlen > (r - l + 1) ? (r - l + 1) : minlen));
			if(l < r) {
				l++;
			}
			else {
				r++;
			}
		}
		else {
			r++;
		}
	}
	cout << (minlen == -1 ? 0 : minlen) << endl;
}