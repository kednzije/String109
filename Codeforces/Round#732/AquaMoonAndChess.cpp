// (x, y) = (x-2, i)
// 			i=0 to y
// i.e.
// (x, y) = (x, y-1) + (x-2, y)
// let a=x/2, b=y
// then let (a, b)=(x, y)
// so (a, b) = (a-1, b) + (a, b-1)
// then we get:
// (a, b) = (b, a)
// guess: (a, b) = C(a, a+b)

#include <iostream>
#include <string>
#include <utility>
#include <map>
using namespace std;
const int MAXN = 1e5 + 5;
const long long MOD = 998244353;
// #define add(x,y) (((x%MOD)+(y%MOD))%MOD)

// map <pair <int, int>, int> ans;
// int getAns(int x, int y) {
// 	if(!x || !y) {
// 		return 1;
// 	}
// 	if(ans.count(make_pair(x, y))) {
// 		return ans[make_pair(x, y)];
// 	}
// 	int res=0;
// 	// for(int i = 0; i <= y; i++) {
// 	// 	res = add(res, getAns(x - 2, i));
// 	// }
// 	res = add(getAns(x, y - 1), getAns(x - 2, y));
// 	ans[make_pair(x, y)] = res;
// 	return res;
// }

typedef long long ll;
inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
inline ll pow(ll a, ll b) {
	ll res=1;
	while(b) {
		if(b & 1) {
			res = mul(res, a);
		}
		b >>= 1, a = mul(a, a);
	}
	return res;
}
inline ll rev(ll a) {
	return pow(a, MOD - 2);
}
ll fact[MAXN];
int getAns(int x, int y) {
	int a = x / 2, b = y;
	return mul(mul(fact[a + b], rev(fact[a])), rev(fact[b]));
}

int main() {
	fact[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fact[i] = mul(i, fact[i - 1]);
	}

	int t;
	cin >> t;
	while(t--) {
		int n;
		string s;
		cin >> n >> s;
		s.push_back('0');
		int x=0, y=-1, cnt=0;
		for(int i = 0; i <= n; i++) {
			if(s[i] == '0') {
				x += cnt - cnt % 2;
				cnt = 0, y++;
			}
			else {
				cnt++;
			}
		}
		cout << getAns(x, y) << endl;
	}
}