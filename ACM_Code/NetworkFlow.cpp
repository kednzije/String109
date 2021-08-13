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
const ll maxn = 10010;
const ll INF = 2147483647;
ll n, m, s, t, tot = 1, head[maxn], nxt[maxn], now[maxn], x, y, v;
ll dis[maxn], res;
struct e{
	ll to, val;
}edge[maxn];
void add_edge(ll x, ll y, ll val){
	nxt[++tot] = head[x];
	edge[tot].to = y;
	edge[tot].val = val;
	head[x] = tot;
}
bool bfs(){
	for(int i = 1; i <= n; i++) dis[i] = INF;
	queue <ll> q;
	dis[s] = 0;
	now[s] = head[s];
	q.push(s);
	while(!q.empty()){
		ll tem = q.front();
		//cout << tem << endl;
		q.pop();
		for(int i = head[tem]; i; i = nxt[i]){
			if(dis[edge[i].to] == INF && edge[i].val){
				//cout << edge[i].to << endl;
				dis[edge[i].to] = dis[tem] + 1;
				now[edge[i].to] = head[edge[i].to];
				q.push(edge[i].to);
				if(edge[i].to == t) return true;
			}
		}
	}
	return false;
}
ll dfs(ll x, ll sum){
	if(x == t) return sum;
	ll ans = 0;
	for(int i = now[x]; i && sum; i = nxt[i]){
		now[x] = i;
		if(dis[edge[i].to] == dis[x] + 1 && edge[i].val){
			ll k = dfs(edge[i].to, min(sum, edge[i].val));
			if(k == 0) dis[edge[i].to] = INF;
			edge[i].val -= k;
			edge[i ^ 1].val += k;
			ans += k;
			sum -= k;
		}
	}
	return ans;
}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> m >> s >> t;
	for(int i = 1; i <= m; i++){
		cin >> x >> y >> v;
		add_edge(x, y, v);
		add_edge(y, x, 0);
	}
	while(bfs()){
		res += dfs(s, INF);
	}
	cout << res << endl;
	return 0;
}