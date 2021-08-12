#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int MAXK = 1e3 + 5;
const long long INF = 1e18;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template <typename T>
void chkmax(T &x, T y) { x = max(x, y); }
template <typename T>
void chkmin(T &x, T y) { x = min(x, y); }
template <typename T>
void read(T &x)
{
	x = 0;
	int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar())
		if (c == '-')
			f = -f;
	for (; isdigit(c); c = getchar())
		x = x * 10 + c - '0';
	x *= f;
}
template <typename T>
void write(T x)
{
	if (x < 0)
		x = -x, putchar('-');
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
void writeln(T x)
{
	write(x);
	puts("");
}
int n, m, k, tot;
vector<vector<int>> c;
vector<pair<int, int>> a[MAXN];
short path[MAXN][MAXK];
ll dp[2][MAXK];
int x[MAXM], y[MAXM], w[MAXM];
int father[MAXN], fedge[MAXN], ans[MAXN];
bool vis[MAXN], instack[MAXN], edge[MAXM];
void dfs(int pos, int fa, int fe)
{
	fedge[pos] = fe;
	father[pos] = fa;
	vis[pos] = instack[pos] = true;
	for (auto x : a[pos])
	{
		if (x.second == fe)
			continue;
		if (!vis[x.first])
			dfs(x.first, pos, x.second);
		else if (instack[x.first])
		{
			vector<int> cur;
			cur.push_back(x.second);
			edge[x.second] = true;
			int tmp = pos;
			while (tmp != x.first)
			{
				cur.push_back(fedge[tmp]);
				edge[fedge[tmp]] = true;
				tmp = father[tmp];
			}
			c.push_back(cur);
		}
	}
	instack[pos] = false;
}
void col(int pos, int c)
{
	ans[pos] = c;
	for (auto x : a[pos])
		if (!ans[x.first] && !edge[x.second])
		{
			col(x.first, c);
		}
}
int main()
{
	int T;
	read(T);
	for (int t = 1; t <= T; t++)
	{
		read(n), read(m), read(k), c.clear();
		for (int i = 1; i <= n; i++)
		{
			a[i].clear();
			vis[i] = false;
		}
		for (int i = 1; i <= m; i++)
		{
			read(x[i]), read(y[i]), read(w[i]), edge[i] = false;
			a[x[i]].emplace_back(y[i], i);
			a[y[i]].emplace_back(x[i], i);
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			if (!vis[i])
			{
				cnt++;
				dfs(i, 0, 0);
			}
		vector<int> lft;
		for (int i = 1; i <= m; i++)
			if (!edge[i])
				lft.push_back(i);
		c.insert(c.begin(), lft);
		int goal = max(k - cnt, 0);
		for (auto &x : c)
		{
			sort(x.begin(), x.end(), [&](int x, int y)
				 { return w[x] < w[y]; });
		}
		tot = c.size() - 1;
		for (int i = 0; i <= tot; i++)
			memset(path[i], -1, sizeof(path[i]));
		for (int i = 1; i <= goal; i++)
		{
			if (i <= c[0].size())
			{
				dp[0][i] = dp[0][i - 1] + w[c[0][i - 1]];
				path[0][i] = 0;
			}
			else
				dp[0][i] = INF;
		}
		for (int i = 0; i <= goal; i++)
		{
			dp[1][i] = dp[0][i];
			path[1][i] = i;
		}
		for (int i = 1, s = 0, t = 1; i <= tot; i++, swap(s, t))
		{
			ll cost = w[c[i][0]];
			for (int j = 1; j <= goal && j < c[i].size(); j++)
			{
				cost += w[c[i][j]];
				for (int k = 0; j + k <= goal; k++)
				{
					if (dp[s][k] + cost < dp[t][j + k])
					{
						dp[t][j + k] = dp[s][k] + cost;
						path[i][j + k] = k;
					}
				}
			}
			for (int j = 0; j <= goal; j++)
			{
				dp[s][j] = dp[t][j];
				path[i + 1][j] = j;
			}
		}
		printf("Case %d: %lld\n", t, dp[tot & 1][goal]);
		for (int i = 1; i <= n; i++)
			ans[i] = 0;
		for (int i = 1; i <= m; i++)
			edge[i] = false;
		int now = goal;
		for (int i = tot; i >= 1; i--)
		{
			int delta = now - path[i][now];
			if (delta)
			{
				for (int j = 0; j <= delta; j++)
					edge[c[i][j]] = true;
			}
			now = path[i][now];
		}
		for (int i = 0; i < now; i++)
			edge[c[0][i]] = true;
		for (int i = 1, cnt = 0; i <= n; i++)
			if (ans[i] == 0)
			{
				cnt = min(cnt + 1, k);
				col(i, cnt);
			}
		for (int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}