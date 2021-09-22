#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
constexpr int mAXN = 200010;
// typedef long long ll;
using ll = long long;

struct Edge
{
	int to, next, w;
} edges[mAXN << 2];
int dis[mAXN], cnt[mAXN], head[mAXN];
bool vis[mAXN];

int edge_cnt, n, m;
ll ans;

int INPUT()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

void add_edge(const int x, const int y, const int z)
{
	edges[++edge_cnt].to = y;
	edges[edge_cnt].next = head[x];
	edges[edge_cnt].w = z;
	head[x] = edge_cnt;
	return;
}
bool SPFA(const int src)
{
	int i, u, v;
	queue<int> que;
	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	que.push(src);
	vis[src] = true;
	dis[src] = 0;
	while (!que.empty())
	{
		u = que.front();
		que.pop();
		vis[u] = false;
		for (i = head[u]; i; i = edges[i].next)
		{
			v = edges[i].to;
			if (dis[v] < dis[u] + edges[i].w)
			{
				dis[v] = dis[u] + edges[i].w;
				if (!vis[v])
				{
					que.push(v);
					vis[v] = true;
					if (++cnt[v] > n)
						return false;
				}
			}
		}
	}
	return true;
}
int main()
{
	// n = INPUT();
	// m = INPUT();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		int k, x, y;
		// k = INPUT();
		// x = INPUT();
		// y = INPUT();
		scanf("%d%d%d", &k, &x, &y);
		switch (k) {
		case 1:
			add_edge(x, y, 0), add_edge(y, x, 0);
			break;
		case 2:
			add_edge(x, y, 1);
			if(x == y) {
				goto Fail;
			}
			break;
		case 3:
			add_edge(y, x, 0);
			break;
		case 4:
			add_edge(y, x, 1);
			if(x == y) {
				goto Fail;
			}
			break;
		case 5:
			add_edge(x, y, 0);
			break;
		
		default:
			break;
		}
	}
	for (int i = n; i >= 1; --i)
		add_edge(0, i, 1);
	if (!SPFA(0))
		goto Fail;
	for (int i = 1; i <= n; ++i)
	{
		ans += dis[i];
	}
	printf("%lld\n", ans);
	goto End;
Fail:
	printf("-1\n");
End:
	return 0;
}