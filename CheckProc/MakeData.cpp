#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    srand(time(NULL));
    freopen("Data.in", "w", stdout);
    cout << rand() % 100 + 1 << ' ' << rand() % 100 + 1 << endl;
}

// #include<bits/stdc++.h>
// using namespace std;
// #define rg register
// const int MAXN=2e5+5;
// int h[MAXN],tot=1,x[MAXN],y[MAXN];
// struct asd{
// 	int to,nxt;
// }b[MAXN<<1];
// void ad(rg int aa,rg int bb){
// 	b[tot].to=bb;
// 	b[tot].nxt=h[aa];
// 	h[aa]=tot++;
// }
// int tp[MAXN];
// bool vis[MAXN];
// void dfs(rg int now,rg int lat){
// 	rg int jud=0;
// 	for(rg int i=h[now];i!=-1;i=b[i].nxt){
// 		rg int u=b[i].to;
// 		if(u==lat) continue;
// 		if(!jud) tp[u]=tp[now],jud=1;
// 		else tp[u]=u;
// 		dfs(u,now);
// 	}
// }
// int main(){
// 	// freopen("/dev/urandom","r",stdin);
//     srand(time(NULL));
//     freopen("Data.in", "w", stdout);
// 	// srand(getchar()*getchar()*getchar()*time(0));
// 	// freopen("data.in","w",stdout);
// 	memset(h,-1,sizeof(h));
// 	int n=rand()%5 000+2,m=n-1;
// 	rg int aa,bb;
// 	tp[1]=1;
// 	for(rg int i=2;i<=n;i++){
// 		aa=rand()%(i-1)+1,bb=i;
// 		x[i-1]=aa,y[i-1]=bb;
// 		ad(aa,bb),ad(bb,aa);
// 	}
// 	dfs(1,0);
// 	rg int cnt=rand()%10+1;
// 	for(rg int i=1;i<=cnt;i++){
// 		aa=rand()%n+1;
// 		bb=tp[aa];
// 		if(aa!=bb && !vis[bb]){
// 			x[++m]=aa,y[m]=bb;
// 			vis[bb]=1;
// 		}
// 	}
//     printf("1\n");
//     int k = rand() % n + 1;
// 	printf("%d %d %d\n",n,m, k);
// 	for(rg int i=1;i<=m;i++){
// 		printf("%d %d %d\n",x[i],y[i], rand() % 50);
// 	}
// 	return 0;
// }
