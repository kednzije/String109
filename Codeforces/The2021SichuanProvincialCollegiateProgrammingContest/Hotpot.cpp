#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int MAXLEN = 1e5 + 5;

int n, k, m;
int ans[MAXLEN];

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(ans, 0, sizeof(ans));
		vector <int> group[MAXLEN];
		cin >> n >> k >> m;
		for(int i = 0; i < n; i++) {
			int gred;
			cin >> gred;
			group[gred].push_back(i);
		}
		for(int i = 1; i <= k; i++) {
			if(group[i].size() % 2) {
				for(int j = 0; j < group[i].size(); j++) {
					ans[group[i][j]] = m / (2 * n);
					if(j % 2) {
						ans[group[i][j]] += (int)(group[i][j] < (m % (2 * n)));
					}
					else {
						ans[group[i][j]] += (int)(group[i][j] + n < (m % (2 * n)));
					}
				}
			}
			else {
				for(int j = 0; j < group[i].size(); j++) {
					if(j % 2) {
						ans[group[i][j]] = m / n + (int)(group[i][j] < (m % n));
					}
					else {
						ans[group[i][j]] = 0;
					}
				}
			}
		}
		for(int i = 0; i < n - 1; i++) {
			cout << ans[i] << ' ';
		}
		cout << ans[n - 1] << endl;
	}
}
/*
4
3 2 6
1 1 2
1 1 5
1
2 2 10
1 2
2 2 10
1 1
*/