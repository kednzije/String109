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
const ll maxn = 200010;
const ll INF = 2147483647;
ll n, q, x, y, dis, p, res, fa[maxn][30], dep[maxn];
vector <ll> e[maxn];
bool vis[maxn];
void dfs(ll x, ll step){
	dep[x] = step;
	vis[x] = 1;
	fa[x][0] = x;
	for(int i = 0; i < e[x].size(); i++){
		if(!vis[e[x][i]]){
			fa[e[x][i]][1] = x;
			for(int j = 2; j < 20; j++) fa[e[x][i]][j] = fa[fa[e[x][i]][j - 1]][j - 1];
			dfs(e[x][i], step + 1);
		}
	}
}
ll lca(ll x, ll y){
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i--) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	//cout << x << " " << y << endl;
	if(x == y) return x;
	for(int i = 19; i >= 0; i--){
		if(dep[fa[x][i]] != dep[fa[y][i]]){
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[y][1];
}
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for(int i = 1; i < n; i++){
		cin >> x >> y;
		e[x].pb(y);
		e[y].pb(x);
	}
	dep[0] = -1;
	dfs(1, 0);
	/*
	for(int i = 1; i <= n; i++){
		cout << i << ": ";
		for(int j = i; j <= n; j++) cout << lca(i, j) << " ";
		cout << endl;
	}
	*/
	while(q--){
		cin >> x >> y;
		p = lca(x, y);
		dis = dep[x] - dep[p] + dep[y] - dep[p] + 1;
		res = n - dis + (dis + 1) * dis / 2;
		cout << res << endl;
	}
	return 0;
}
