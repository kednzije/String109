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
const ll maxn = 1000010;
const ll INF = 2147483647;
ll n, m, cnt, a[maxn];
priority_queue <ll, vector<ll>, greater<ll> > q1;
priority_queue <ll, vector<ll>, less<ll> > q2;
int main()
{ 
	freopen("Data.in", "r", stdin);
    freopen("AcceptedRes.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> m >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++){
		cnt = i / m + (i % m == 0 ? 0 : 1);
		if(q1.size() < cnt) q1.push(a[i]);
		else q2.push(a[i]);
		while(!q1.empty() && !q2.empty() && q2.top() > q1.top()){
			ll tem1 = q1.top();
			q1.pop();
			ll tem2 = q2.top();
			q2.pop();
			q1.push(tem2);
			q2.push(tem1);
		}
		cout << q1.top() << " ";
	}
	return 0;
}
