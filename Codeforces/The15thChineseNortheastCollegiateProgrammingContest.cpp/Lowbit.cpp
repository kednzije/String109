#include<cstdio>
#include<iostream>
using namespace std;
#define maxn 100000

int a[maxn+5];
int tag[maxn+5];

#define lowbit(x) ((x) & -(x))

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=0;
			tag[i]=0;
		}
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			int op,l,r;
			scanf("%d%d%d",&op,&l,&r);
			if(lowbit(a[l])==a[l])tag[l]=1;
			if(tag[l])a[l]=(2*a[l])%998244353;
			else a[l]=a[l]+lowbit(a[l]);
		}
		for(int i=1;i<=n;i++)ans=(ans+a[i])%998244353;
		cout<<ans<<endl;
	}
}