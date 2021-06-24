#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <iomanip>
using namespace std;
constexpr int MAXN = 1005;
constexpr double pi = 3.14159265359;

vector <int> edges[MAXN];
set <int> seen;
pair <double, double> points[MAXN];

void dfs(int pos, double l, double r) {
	double theta = 1.0 * (r - l) / edges[pos].size();
	for(int i = 0; i < edges[pos].size(); i++) {
		int nxt_pos = edges[pos][i];
		if(seen.count(nxt_pos) > 0) {
			continue;
		}
		seen.insert(nxt_pos);
		points[nxt_pos] = make_pair(
			points[pos].first + cos((l + i * theta) * pi), 
			points[pos].second + sin((l + i * theta) * pi));
		dfs(nxt_pos, l + i * theta, l + (i + 1) * theta);
	}
}

int main() {
	int n, max_deg = -1;
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		edges[u].emplace_back(v), edges[v].emplace_back(u);
	}
	for(int i = 1; i <= n; i++) {
		if(-1 == max_deg || edges[i].size() > edges[max_deg].size()) {
			max_deg = i;
		}
	}
	seen.insert(max_deg), points[max_deg] = make_pair(0, 0);
	dfs(max_deg, 0, 2);
	for(int i = 1; i <= n; i++) {
		cout << fixed << setprecision(7) << points[i].first << ' ' << points[i].second << endl;
	}
}