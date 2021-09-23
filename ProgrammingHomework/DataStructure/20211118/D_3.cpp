#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
constexpr int MAXN = 10010;
constexpr int INF = 1e9 + 7;

inline int get_min(int a, int b) {
	return a < b ? a : b;
}

int n, son[MAXN][2], first_son, second_son, dp[MAXN][3];
string inputs[MAXN];
void dfs(int node){
	if(son[node][0] != -1) {
		dfs(son[node][0]);
	}
	if(son[node][1] != -1) {
		dfs(son[node][1]);
	}
	if(son[node][0] == -1 && son[node][1] == -1) {
		dp[node][1] = get_min(dp[node][1], 1);
		dp[node][0] = get_min(dp[node][0], 0);
		return;
	}
	int sum = 0;
	for(int i = 0; i < 2; i++) {
		if(son[node][i] == -1) {
			continue;
		}
		sum += get_min(dp[son[node][i]][1], get_min(dp[son[node][i]][0], dp[son[node][i]][2]));
	}
	dp[node][1] = get_min(dp[node][1], sum + 1);
	sum = 0;
	for(int i = 0; i < 2; i++) {
		if(son[node][i] == -1) {
			continue;
		}
		sum += dp[son[node][i]][2];
	}
	dp[node][0] = get_min(dp[node][0], sum);
	sum = INF;
	for(int i = 0; i < 2; i++) {
		if(son[node][i] == -1) {
			continue;
		}
		int cur = 0;
		for(int j = 0; j < 2; j++) {
			if(son[node][j] == -1) {
				continue;
			}
			if(i == j) cur += dp[son[node][j]][1];
			else cur += get_min(dp[son[node][j]][1], dp[son[node][j]][2]);
		}
		sum = get_min(sum, cur);
	}
	dp[node][2] = get_min(dp[node][2], sum);
}
int main()
{
	memset(dp, 0x3f, sizeof(dp));
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> inputs[i];
	}
	first_son = 1;
	second_son = 2;
	memset(son, -1, sizeof(son));
	while(second_son <= n){
		if(inputs[first_son] == "null"){
			first_son++;
			continue;
		}
		if(inputs[second_son] == "null"){
			son[first_son][0] = -1;
		}
		else{
			son[first_son][0] = second_son;
		}
		second_son++;
		if(second_son > n) break;
		if(inputs[second_son] == "null"){
			son[first_son][1] = -1;
		}
		else{
			son[first_son][1] = second_son;
		}
		second_son++;
		first_son++;
	}
	dfs(1);
	cout << get_min(dp[1][2], dp[1][1]);
	return 0;
}