```c++
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
typedef pair<ll,ll> pii;
const ll maxn = 100010;
const ll INF = 2147483647;
ll n, m, s, t, tot = 1, head[maxn], now[maxn], dis[maxn], nxt[maxn];
ll res, r_cost, vol, cost, x, y;
bool vis[maxn];
struct e{
	ll to, vol, cost;
}edge[maxn];
void add_edge(ll x, ll y, ll vol, ll cost){
	nxt[++tot] = head[x];
	edge[tot].to = y;
	edge[tot].vol = vol;
	edge[tot].cost = cost;
	head[x] = tot;
	return;
}
bool spfa(){
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++) dis[i] = INF;
	queue <ll> q;
	dis[s] = 0;
	now[s] = head[s];
	vis[s] = 1;
	q.push(s);
	while(!q.empty()){
		ll tem = q.front();
		q.pop();
		vis[tem] = 0;
		for(int i = head[tem]; i; i = nxt[i]){
			if(dis[edge[i].to] > dis[tem] + edge[i].cost && edge[i].vol){
				dis[edge[i].to] = dis[tem] + edge[i].cost;
				if(!vis[edge[i].to]){
					now[edge[i].to] = head[edge[i].to];
					vis[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
		}
	}
	return dis[t] != INF;
}
ll dfs(ll x, ll sum){
	if(x == t) return sum;
	vis[x] = 1;
	ll ans = 0;
	for(int i = now[x]; i && sum; i = nxt[i]){
		now[x] = i;
		if((!vis[edge[i].to] || edge[i].to == t) && edge[i].vol && dis[edge[i].to] == dis[x] + edge[i].cost){
			ll k = dfs(edge[i].to, min(sum, edge[i].vol));
			if(k == 0) dis[edge[i].to] = INF;
			edge[i].vol -= k;
			edge[i ^ 1].vol += k;
			ans += k;
			sum -= k;
			r_cost += k * edge[i].cost;
		}
	}
	return ans;
}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> m >> s >> t;
	for(int i = 1; i <= m; i++){
		cin >> x >> y >> vol >> cost;
		add_edge(x, y, vol, cost);
		add_edge(y, x, 0, -cost);
	}
	while(spfa()){
		vis[t] = 1;
		while(vis[t]){
			memset(vis, 0, sizeof(vis));
			res += dfs(s, INF);
		}
	}
	cout << res << " " << r_cost << endl;
	return 0;
}
```

