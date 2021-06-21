#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
using namespace std;
constexpr int prime[] = {
	0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
};
constexpr int MAXN = 30005;
using ll = long long;

ll n[MAXN];
int k;
vector <int> inds[20];
map <int, ll> ans;

void dfs(int pos, int cnt, const int tar, ll now) {
	if(cnt == tar) {
		for(auto ind: inds[k]) {
			ans[ind] += (tar % 2 == 1 ? 1 : -1) * (n[ind] / now);
		}
		return;
	}
	for(int i = pos + 1; i <= k - (tar - cnt) + 1; i++) {
		dfs(i, cnt + 1, tar, now * prime[i]);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++) {
		scanf("%lld%d", &n[i], &k);
		inds[k].push_back(i);
	}

	for(k = 1; k <= 16; k++) {
		for(int i = 1; i <= k; i++) {
			dfs(0, 0, i, 1);
		}
	}
	for(auto _ans: ans) {
		printf("%lld\n", n[_ans.first] - _ans.second);
	}
}