/*
    Author:Frozencode
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 100010;
const int INF = 2147483647;
int n, m, k, a[maxn], p1, p2;
ll res;
struct node
{
	int minn, maxx;
} s[maxn << 2];
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }
// #define ls(p) (p << 1)
// #define rs(p) (p << 1 | 1)
void build(int p, int l, int r)
{
	if (l == r)
	{
		s[p].minn = s[p].maxx = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	s[p].minn = min(s[ls(p)].minn, s[rs(p)].minn);
	s[p].maxx = max(s[ls(p)].maxx, s[rs(p)].maxx);
}
int qry_minn(int p, int l, int r, int nl, int nr)
{
	if (nl <= l && nr >= r)
		return s[p].minn;
	int mid = (l + r) >> 1;
	int res = INF;
	if (nl <= mid)
		res = min(res, qry_minn(ls(p), l, mid, nl, nr));
	if (nr > mid)
		res = min(res, qry_minn(rs(p), mid + 1, r, nl, nr));
	return res;
}
int qry_maxx(int p, int l, int r, int nl, int nr)
{
	if (nl <= l && nr >= r)
		return s[p].maxx;
	int mid = (l + r) >> 1;
	int res = -1;
	if (nl <= mid)
		res = max(res, qry_maxx(ls(p), l, mid, nl, nr));
	if (nr > mid)
		res = max(res, qry_maxx(rs(p), mid + 1, r, nl, nr));
	return res;
}
int main()
{
	freopen("1.txt", "r", stdin);
	freopen("2.txt", "w", stdout);
	clock_t startTime, endTime;
	startTime = clock();
	// cin >> n >> m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		// cin >> a[i];
		scanf("%d", &a[i]);
	build(1, 1, n);

	endTime = clock(); //计时结束
	printf("The run time is: %lfs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

	for (int i = 1; i <= m; i++)
	{
		// cin >> k;
		scanf("%d", &k);
		p1 = 1;
		p2 = 1;
		res = 0;
		while (p2 <= n)
		{
			while (p2 == 1 || ((qry_maxx(1, 1, n, p1, p2) - qry_minn(1, 1, n, p1, p2) <= k) && p2 <= n))
			{
				p2++;
			}
			if (p2 > n)
				break;
			res += n - p2 + 1;
			p1++;
		}
		while ((qry_maxx(1, 1, n, p1, p2 - 1) - qry_minn(1, 1, n, p1, p2 - 1) > k) && p1 < n)
		{
			res++;
			p1++;
		}
		// cout << res << "\n";
		printf("%d\n", res);
	}
	endTime = clock(); //计时结束
	// cout << "The run time is:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	printf("The run time is: %lfs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	return 0;
}