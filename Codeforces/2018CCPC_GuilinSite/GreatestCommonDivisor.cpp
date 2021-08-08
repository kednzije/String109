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
const ll maxn = 500010;
const ll INF = 2147483647;
ll t, n, a[maxn];
int main()
{ 
	ios::sync_with_stdio(false);
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> n;
		for(int j = 1; j <= n; j++) cin >> a[j];
		sort(a + 1, a + n + 1);
		n = unique(a + 1, a + n + 1) - a - 1;
		// cout << n << endl;
		cout << "Case " << i << ": ";	
		if(n == 1){
			if(a[1] != 1) cout << 0 << endl;
			else cout << -1 << endl;
			continue;
		}
		ll tem = abs(a[2] - a[1]);
		// cout << tem << endl;
		for(int j = 2; j < n; j++) tem = __gcd(tem, abs(a[j + 1] - a[j]));
		// cout << tem << endl;
		if(tem == 1){
			cout << -1 << endl;
			continue;
		}
		else{
			cout << ((a[1] % tem == 0) ? 0 : (tem - a[1] % tem)) << endl;
		}
	}
	return 0;
}