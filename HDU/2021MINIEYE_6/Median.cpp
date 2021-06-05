/*
	Author:Frozencode
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 100010;
const ll INF = 2147483647;
ll t, n, m, head, pos, tot, tem, nxt[maxn], a[maxn];
bool flag, vis[maxn];
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--){
		cin >> n >> m;
		for(int i = 1; i <= n; i++) vis[i] = 0;
		vis[n + 1] = 0;
		pos = n + 1;
		tot = 0;
		for(int i = 1; i <= m; i++){
			cin >> a[i];
			vis[a[i]] = 1;
		}
		sort(a + 1, a + m + 1);
		for(int i = n + 1; i >= 1; i--){
			if(!vis[i]){
				nxt[i] = pos;
				pos = i;
			}
		}
		flag = true;
		for(int i = 1; i <= n; i++){
			if(pos == n + 1) break;
			if(vis[i]){
				if(pos <= n && pos > i){
					if(pos < a[m]) tot += 1;
					pos = nxt[pos];
				}
				else{
					ll cnt = 0;
					while(pos < i){
						cnt++;
						pos = nxt[pos];
					}
					for(int j = 1; j <= cnt; j++){
						if(pos == n + 1){
							flag = false;
							break;
						}
						if(pos < a[m]) tot += 2;
						pos = nxt[pos];
					}
					if(pos != n + 1){
						if(pos < a[m]) tot += 1;
						pos = nxt[pos];
					}
				}
			}
		}
		if(pos != n + 1){
			ll tem = 0;
			while(pos != n + 1){
				tem++;
				pos = nxt[pos];
			}
			if(tem > tot) flag = false;
		}
		//cout << tot << endl;
		cout << (flag ? "YES" : "NO") << endl;
		//for(int i = 1; i <= n; i++) cout << nxt[i] << " \n"[i == n];
	}
	return 0;
}