#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxl=2e5+10;
const int mod=1e9+7;
 
int n,m,cas,nowl;bool circflag;ll ans,inv10;
ll mi[maxl];
int a[maxl],b[maxl],nxt[maxl];
struct cir{int st,ed;} c;
vector<int> now,tmp;
struct ed{int v,w;};
vector<ed> e[maxl];
vector<int> fe[maxl];
bool vis1[maxl];
 
inline void prework()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		e[i].clear();fe[i].clear();
		vis1[i]=false;
	}
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].push_back(ed{v,w});
		fe[v].push_back(u);
	}
	queue<int> q;
	q.push(1);vis1[1]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int v:fe[u])
		if(!vis1[v])
			vis1[v]=true,q.push(v);
	}
}
 
inline void mainwork()
{
	nowl=0;now.clear();
	now.push_back(0);
	circflag=false;
	while(nowl<=2*n)
	{
		sort(now.begin(),now.end());
		now.erase(unique(now.begin(),now.end()),now.end());
		int mi=10;tmp.clear();
		for(int u:now)
			for(ed ee:e[u])
			if(vis1[ee.v])
			{
				if(ee.w<mi)
				{	
					tmp.clear();mi=ee.w;
					tmp.push_back(ee.v);
				}
				else if(ee.w==mi)
					tmp.push_back(ee.v);
			}
		a[++nowl]=mi;
		now.clear();
		for(int u:tmp)
		{
			now.push_back(u);
			if(u==1)
				return;
		}
	}
	circflag=true;int len=0;
	for(int i=n;i<=2*n;i++)
		b[++len]=a[i];
	int j=0;
	for(int i=2;i<=len;i++)
	{
		while(j && b[j+1]!=b[i])
			j=nxt[j];
		if(b[j+1]==b[i])
			j++;
		nxt[i]=j;
	}
	c.st=n;c.ed=n+(len-nxt[len])-1;
}
 
inline ll qp(ll a,ll b)
{
	ll ans=1,cnt=a;
	while(b)
	{
		if(b&1)
			ans=ans*cnt%mod;
		cnt=cnt*cnt%mod;
		b>>=1;	
	}
	return ans;
}
 
inline void print()
{
	if(!circflag)
	{
		ans=0;
		for(int i=nowl;i>=1;i--)
			ans=(a[i]+ans)*inv10%mod;
	}
	else
	{
		ll cirans=0,t;
		for(int i=c.st;i<=c.ed;i++)
			cirans=(a[i]+cirans*10)%mod;
		t=qp(mi[c.st-1],mod-2)*qp((mi[c.ed-c.st+1]-1+mod)%mod,mod-2)%mod;
		ans=0;
		for(int i=c.st-1;i>=1;i--)
			ans=(a[i]+ans)*inv10%mod;
		//	printf("%d\n",ans);
		//	printf("%d\n",cirans);
		ans=(ans+cirans*t%mod)%mod;
	}
	printf("Case #%d: %lld\n",++cas,ans);
}
 
int main()
{
	freopen("Data.in", "r", stdin);
    freopen("AcceptedRes.out", "w", stdout);
	//printf("%d\n",qp(99,mod-2)*31%mod);
	inv10=qp(10,mod-2);
	mi[0]=1;
	for(int i=1;i<maxl;i++)
		mi[i]=mi[i-1]*10%mod;
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		prework();
		mainwork();
		print();
	}
	return 0;
}