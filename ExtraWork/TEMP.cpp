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
ll n;
char ch[3005][3005];
pii dir[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
char turn(ll x){
      switch(x){
            case 0: return 'L';
            case 1: return 'U';
            case 2: return 'R';
            case 3: return 'D';
            default: return '?';
      }
}
void dfs(ll x, ll y, ll cnt){
      //cout << x << " " << y << endl;
      bool flag = false;
      int i = cnt;
      if(ch[x + dir[i].fi][y + dir[i].se] != 'U' && ch[x + dir[i].fi][y + dir[i].se] != 'D' && ch[x + dir[i].fi][y + dir[i].se] != 'L' && ch[x + dir[i].fi][y + dir[i].se] != 'R'){
            ch[x][y] = turn(i);
            flag = true;
            dfs(x + dir[i].fi, y + dir[i].se, i);
      }
      else{
            i = (cnt + 1) % 4;
            if(ch[x + dir[i].fi][y + dir[i].se] != 'U' && ch[x + dir[i].fi][y + dir[i].se] != 'D' && ch[x + dir[i].fi][y + dir[i].se] != 'L' && ch[x + dir[i].fi][y + dir[i].se] != 'R'){
                  ch[x][y] = turn(i);
                  flag = true;
                  dfs(x + dir[i].fi, y + dir[i].se, i);
            }
      }
      if(!flag) ch[x][y] = 'U';
}
int main() {
      //freopen("1.in", "w", stdout);
      cout << 1 << endl;
      n = 200;
      cout << n << " " << n << endl;
      for(int i = 1; i <= n; i++) ch[1][i] = 'D';
      for(int i = 1; i <= n; i++) ch[n][i] = 'U';
      for(int i = 2; i < n; i++) ch[i][1] = 'R';
      for(int i = 2; i < n; i++) ch[i][n] = 'L';
      dfs(n - 1, n - 1, 0);
      for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++) cout << ch[i][j];
            cout << endl;
      }
}
