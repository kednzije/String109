#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long

ll n,m,s,sum;

struct hum
{
	ll num,t;
};

hum a[100005];
int cmp(hum a,hum b){return a.t>b.t;}

int cmp2(hum a,hum b){return a.num<b.num;}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		a[i].num=i;
		cin>>a[i].t;sum+=a[i].t;
	}
	sort(a+1,a+1+n,cmp);
	s=max(a[1].t,(sum%m)?(sum/m+1):(sum/m));
	int nowm=1,nowl=0;
	
	sort(a+1,a+1+n,cmp2);
	for(int i=1;i<=n;i++)
	{
		if(nowl+a[i].t<=s)
		{
			cout<<"1 "<<nowm<<" "<<nowl<<" "<<nowl+a[i].t<<endl;
			nowl=nowl+a[i].t;
			if(nowl==s)
			{
				nowl=0;
				nowm++;
			}
		}
		else
		{
			cout<<"2 ";
			int tempm=nowm,templ=nowl;
			a[i].t-=(s-nowl);
			nowl=0;
			nowm++;
			cout<<nowm<<" "<<nowl<<" "<<nowl+a[i].t<<" ";
			cout<<tempm<<" "<<templ<<" "<<s<<endl;
			nowl=nowl+a[i].t;
			if(nowl==s)
			{
				nowl=0;
				nowm++;
			}
		}
	}
	
}