#include <bits/stdc++.h>
#define ll long long
#define db long double
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()

using namespace std;

const int mod = 1000000007;

void add(int& a, int b) {
  a += b;
  if (a >= mod) a -= mod;
  if (a < 0) a += mod;
}

int mult(int a, int b) {
  return a * (ll)b % mod;
}

int bp(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) res = mult(res, a);
    a = mult(a, a);
    b >>= 1;
  }
  return res;
}

vector<int> w;
vector<vector<pair<int, int> > > gr;

vector<bool> used;
vector<bool> eused;
vector<vector<int> > tot;

void dfs(int vertex, int led, vector<pair<int, int> > &path) {

	path.pb(mp(vertex, led));
	used[vertex] = true;

	for (auto to : gr[vertex]) {
		if (used[to.x]) {
			if (eused[to.y]) continue;
			if (to.y == led) continue;
			vector<int> G;
			for (int i = path.size() - 1; i >= 0; --i) {
				G.pb(path[i].y);
				if (path[i - 1].x == to.x) break;
			}
			G.pb(to.y);
			for (auto ed : G) eused[ed] = true;
			tot.pb(G);
			continue;
		}
		dfs(to.x, to.y, path);
	}
	path.pop_back();

}

short int go[100007][1007];

bool cmp(int x, int y) {
	return (w[x] < w[y]);
}

vector<int> color;
int Q = 0;

void dfs2(int vertex) {
	color[vertex] = Q;
	for (auto to : gr[vertex]) {
		if (eused[to.y] || color[to.x] != -1) continue;
		dfs2(to.x);
	}
}

void solve(int test) {

	cout << "Case " << test << ": ";

	int n, m, k;
	cin >> n >> m >> k;

	gr.assign(n, {});
	w.assign(m, -1);

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v >> w[i];
		u--, v--;
		gr[u].pb(mp(v, i));
		gr[v].pb(mp(u, i));
	}

	used.assign(n, false);
	eused.assign(m, false);
	tot.clear();

	int conn = 0;


	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			conn++;
			vector<pair<int, int> > path;
			dfs(i, -1, path);
		}
	}

	for (int i = 0; i < m; ++i) {
		if (!eused[i]) {
			vector<int> W;
			W.pb(i);
			tot.pb(W);
		}
	}

	for (auto &x : tot) sort(all(x), cmp);
	vector<ll> dp(k + 1, 1e18);
	dp[0] = 0;
	for (int i = 0; i < tot.size(); ++i) {
		vector<ll> dp2(k + 1, 1e18);
		for (int j = 0; j <= k; ++j) {
			ll spend = 0;
			short int best = -1;

			for (int take = 0; take <= min(k + 1, (int) tot[i].size()); ++take) {
				int R = take;
				if (tot[i].size() > 1) R--;
				if (R < 0) R++;

				if (R <= j) {
					ll W = dp[j - R] + spend;
					if (W < dp2[j]) {
						dp2[j] = W;
						best = take;
					}
				}
				else break;
				if (take != tot[i].size()) spend += w[tot[i][take]];
			}

			go[i + 1][j] = best;
		}
		dp = dp2;
	}

	//cout << go[2][2] << endl;

	vector<int> dlt;
	int cur = max(k - conn, 0);

	for (int i = tot.size(); i > 0; --i) {
		int take = go[i][cur];
		for (int j = 0; j < take; ++j) dlt.pb(tot[i - 1][j]);

		if (take > 0 && tot[i - 1].size() > 1) take--;
		cur -= take;
	}

	eused.assign(m, false);
	for (auto x : dlt) {
		eused[x] = true;
	}
	ll ans = 0;

	for (int i = 0; i < m; ++i) if (eused[i]) {
		ans += w[i];
	}

	color.assign(n, -1);

	cout << ans << '\n';
	Q=0;
	for (int i = 0; i < n; ++i) {
		if (color[i] == -1) {
			dfs2(i);
			if (Q + 1 < k) Q++;
		}
	}

	// for (auto c : color) cout << c+1 << " ";
	// cout << '\n';

	

} 

int main(){
{
	freopen("Data.in", "r", stdin);
    freopen("AcceptedRes.out", "w", stdout);
#ifdef LOCAL
	freopen("E_input.txt", "r", stdin);
	//freopen("E_output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; ++i) solve(i + 1);

}
