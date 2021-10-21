#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
inline ll get_max(ll a, ll b)
{
	return a > b ? a : b;
}
inline ll get_min(ll a, ll b)
{
	return a < b ? a : b;
}
inline ll input()
{
	static ll num, sign;
	static char c;
	num = 0, sign = 1;
	c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
		{
			sign = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		num = num * 10 + (c - '0');
		c = getchar();
	}
	return sign * num;
}
constexpr ll MAXN = 1e5 + 10;

ll n, m, u, v, res, deg[MAXN], val[MAXN];
pair<int, int> edge[MAXN];
vector<ll> good_node;
bool vis[MAXN];
set<ll> s[MAXN]; // record the node which can form a triangle
bool cmp(pair<int, int> u, pair<int, int> v)
{
	return val[u.first] + val[u.second] > val[v.first] + val[v.second];
}
int main()
{
	n = input(), m = input();
	for (int i = 0; i < n; i++)
	{
		val[i] = input();
	}
	for (int i = 1; i <= m; i++)
	{
		edge[i].first = input(), edge[i].second = input();
		deg[edge[i].first]++;
		deg[edge[i].second]++;
	}
	for (int i = 0; i < n; i++)
	{
		if (deg[i] > 1)
		{
			good_node.push_back(i);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		if (deg[edge[i].first] < 2 || deg[edge[i].second] < 2)
		{
			continue;
		}
		s[edge[i].first].insert(edge[i].second);
		s[edge[i].second].insert(edge[i].first);
	}
	bool good = false;
	for (int i = 0; i < good_node.size(); i++)
	{
		ll root = good_node[i];
		vector<pair<int, int>> use;
		for (auto node1 : s[root])
		{
			for (auto node2 : s[root])
			{
				if (node2 == node1)
				{
					break;
				}
				if (s[node1].find(node2) != s[node1].end()) // node1 could reach node2
				{
					good = true;
					use.push_back({node1, node2});
				}
			}
		}
		if (use.empty())
		{
			continue;
		}
		sort(use.begin(), use.end(), cmp);
		set<ll> cur;
		cur.insert(use[0].first), cur.insert(use[0].second);
		ll base1 = val[use[0].first] + val[use[0].second], tem1 = base1;
		for (int i = 1; i < use.size(); i++)
		{
			u = use[i].first, v = use[i].second;
			tem1 = get_max(tem1, base1 + (cur.find(u) == cur.end() ? val[u] : 0) + (cur.find(v) == cur.end() ? val[v] : 0));
		}
		ll tem2 = 0, cnt1 = 0, cnt2 = 0;
		vector<pair<int, int>> node1, node2;
		for (int i = 1; i < use.size(); i++)
		{
			u = use[i].first, v = use[i].second;
			if (cnt1 < 2 && (u == use[0].first || v == use[0].first))
			{
				cnt1++;
				node1.push_back(use[i]);
			}
			if (cnt2 < 2 && (u == use[0].second || v == use[0].second))
			{
				cnt2++;
				node2.push_back(use[i]);
			}
		}
		for (auto p1 : node1)
		{
			for (auto p2 : node2)
			{
				set<ll> helper;
				helper.insert(p1.first), helper.insert(p1.second);
				helper.insert(p2.first), helper.insert(p2.second);
				ll sum = 0;
				for (auto num : helper)
				{
					sum += val[num];
				}
				tem2 = get_max(tem2, sum);
			}
		}
		res = get_max(res, val[root] + get_max(tem1, tem2));
	}
	cout << (good ? res : 0);
	return 0;
}