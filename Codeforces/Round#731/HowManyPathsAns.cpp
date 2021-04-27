#include <cstdio>
#include <cstring>
using namespace std;
const int N=4e5+10;
struct rec{
	int pre,to;
}a[N];
int n,m,head[N],used[N],tot;
bool onc[N],dd[N];
void del() {
	tot=0;
	for (int i=1;i<=n;i++) {
		head[i]=0;
		used[i]=0;
		onc[i]=false;
		dd[i]=false;
	}
}
void adde(int u,int v) {
	a[++tot].pre=head[u];
	a[tot].to=v;
	head[u]=tot;
} 
void dfs(int u) {
	used[u]=1;
	for (int i=head[u];i;i=a[i].pre) {
		int v=a[i].to;
		if (used[v]==1) onc[v]=1;
		else if (used[v]==2) dd[v]=1;
		else dfs(v);
	}
	used[u]=2;
}
void dfs1(int u) {
	for (int i=head[u];i;i=a[i].pre) {
		int v=a[i].to; 
		if (!onc[v]) {
			onc[v]=1; dfs1(v);
		}
	}
}
void dfs2(int u) {
	for (int i=head[u];i;i=a[i].pre) {
		int v=a[i].to; 
		if (!dd[v]) {
			dd[v]=1; dfs2(v);
		}
	}
}
int main() {
	int t; scanf("%d",&t);
	while (t--) {
		scanf("%d%d",&n,&m);
		for (int i=1;i<=m;i++) {
			int u,v; scanf("%d%d",&u,&v);
			adde(u,v);
		}
		dfs(1);
		for (int i=1;i<=n;i++) {
			if (onc[i]) dfs1(i);
			if (dd[i]) dfs2(i);
		}
		for (int i=1;i<=n;i++) {
			if (!used[i]) printf("0 ");
			else if (onc[i]) printf("-1 ");
			else if (dd[i]) printf("2 ");
			else printf("1 ");
		}
		puts("");
		del();
	}
	return 0;
}