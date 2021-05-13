#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
constexpr int MAXN = 55;
constexpr int MAXM = 15005;
constexpr int MAXT = 505;
constexpr int INF = 1e5;
constexpr double EPS = 1e-6;
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}
inline double abs(double k) {
	return k > 0 ? k : -k;
} 
inline bool unequal(double a, double b) {
	return abs(a - b) > EPS;
}

map <string, vector <pair <int, int>>> materials;
int dp[MAXN][MAXT], costs[MAXN];
string courses[MAXN];
set <int> plans[MAXN][MAXT];
pair <int, int> choices[MAXN], unchosen[MAXM];
int score[MAXN];
bool chosen[MAXN];

int main() {
	int t;
	cin >> t;
	while(t--) {
		memset(dp, 0, sizeof(dp));
		memset(score, 0, sizeof(score));
		memset(chosen, false, sizeof(chosen));
		materials.clear();
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			string s;
			cin >> s;
			courses[i] = s;
			costs[i] = INT_MAX;
		}
		int m;
		cin >> m;
		for(int i = 1; i <= m; i++) {
			string s;
			int x, y;
			cin >> s >> x >> y;
			materials[s].push_back(make_pair(x, y));
		}
		int t, p;
		cin >> t >> p;
		for(int k = 1; k <= n; k++) {
			for(int j = 1; j <= t; j++) {
				plans[k][j].clear();
			}
			costs[k] = INF;
			for(int i = 0; i < materials[courses[k]].size(); i++) {
				for(int j = t; j >= 1; j--) {
					auto material = materials[courses[k]][i];
					if(material.second <= j && dp[k][j] < dp[k][j - material.second] + material.first) {
						dp[k][j] = dp[k][j - material.second] + material.first;
						plans[k][j].insert(i);
					}

					if(dp[k][j] >= 60) {
						costs[k] = min(costs[k], j);
					}
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			choices[i] = make_pair(costs[i], i);
		}
		sort(choices + 1, choices + 1 + n);
		int tot = 0;
		for(int i = 1; i <= n - p; i++) {
			if(choices[i].first >= INF) {
				tot = -1;
				break;
			}
			tot += choices[i].first;
			t -= costs[choices[i].second];
			chosen[choices[i].second] = true;
			score[choices[i].second] = dp[choices[i].second][costs[choices[i].second]];
		}
		if(tot == -1) {
			cout << -1 << endl;
		}
		int cnt = 0;
		for(int k = 1; k <= n; k++) {
			for(int i = 0; i < materials[courses[k]].size(); i++) {
				if(chosen[k] && plans[k][costs[k]].count(i)) {
					continue;
				}
				unchosen[++cnt] = materials[courses[k]][i];
			}
		}
		sort(unchosen + 1, unchosen + 1 + cnt,
			[](const pair <int, int>& a, const pair <int, int>& b) {
				if(unequal(1.0 * a.first / a.second, 1.0 * b.first / b.second)) {
					return a.second < b.second;
				}
				return 1.0 * a.first / a.second > 1.0 * b.first / b.second;
			});
		
	}
}