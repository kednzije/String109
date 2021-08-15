/**
 * @file KM.cpp
 * @author String
 * @brief 
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
constexpr int MAXN = 10005;
constexpr int MAXM = 100005;
 
int to[MAXN][MAXN], n, m, e;
int matchx[MAXN], matchy[MAXN];
bool vis[MAXN];
bool dfs(int u) {
    for(int v = n + 1; v <= n + m; v++) if(to[u][v]) {
        if(vis[v]) continue;
        vis[v] = true;
        if(!matchy[v] || dfs(matchy[v])) {
            matchx[u] = v, matchy[v] = u;
            return true;
        }
    }
    return false;
}
 
int main() {
    scanf("%d%d%d", &n, &m, &e);
    for(int i = 1; i <= e; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a < 1 || a > n || b < 1 || b > m) continue;
        to[a][b + n] = to[b + n][a] = true;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++) {
        if(!matchx[i]) {
            memset(vis, false, sizeof(vis));
            ans += dfs(i);
        }
    }
    printf("%d\n", ans);
    return 0;
}