#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int MOD = 998244353;
inline ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
inline ll mul(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
inline ll pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a), b >>= 1;
	}
	return res;
}
inline ll rev(ll a) {
	return pow(a, MOD - 2);
}
inline ll divi(ll a, ll b) {
	return mul(a, rev(b));
}

constexpr int MAXN = 5005;
int n;
ll nums[MAXN];
bool vis[MAXN];
vector <ll> lens;

int main() {
	cout << divi(5, 3) << endl;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int ind = 0;
	for(int i = 0; i < n; i++) {
		if(vis[i]) {
			continue;
		}
		int cnt = 1;
		ind = i, vis[i] = true;
		for(int j = i + 1; j < n; j++) {
			if(!vis[j] && nums[j] >= nums[ind]) {
				cnt++;
				ind = j, vis[j] = true;
			}
		}
		lens.emplace_back(cnt);
	}
	for(auto len: lens) {
		cout << len << endl;
	}
}