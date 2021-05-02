#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long

ll n,a,b,c;
ll dp[5005][5005];
ll rec[5005][5005][2];

struct choice
{
	ll a,b,c;
};

choice cc[5005];

bool cmp(choice x, choice y)
{
	return (x.a-x.b)>(y.a-y.b);
}

int main()
{
	freopen("Data.in", "r", stdin);
    freopen("WrongRes.out", "w", stdout);
	//freopen("test.in","r",stdin);
	cin>>n>>a>>b>>c;
	for(int i=1;i<=n;i++)
	{
		cin>>cc[i].a>>cc[i].b>>cc[i].c;
	}
	sort(cc+1,cc+1+n,cmp);
	//cout<<endl;
	//for(int i=1;i<=n;i++)
	//cout<<cc[i].a<<" "<<cc[i].b<<" "<<cc[i].c<<endl;
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<=c&&j<=i;j++)
		{
			if((i==j)||
			(j-1>=0&&rec[i-1][j][0]<a&&(dp[i-1][j-1]+cc[i].c>dp[i-1][j]+cc[i].a)||
			(rec[i-1][j][1]<b && rec[i-1][j][0]==a && dp[i-1][j-1]+cc[i].c>dp[i-1][j]+cc[i].b)))
			{
				//cout<<i<<" "<<j<<"c"<<endl;
				dp[i][j]=dp[i-1][j-1]+cc[i].c;
				rec[i][j][0]=rec[i-1][j-1][0];
				rec[i][j][1]=rec[i-1][j-1][1];
			}
			else
			{
				if(rec[i-1][j][0]<a)
				{
					//cout<<i<<" "<<j<<"a"<<endl;
					dp[i][j]=dp[i-1][j]+cc[i].a;
					rec[i][j][0]=rec[i-1][j][0]+1;
					rec[i][j][1]=rec[i-1][j][1];
				}
				else
				{
					//cout<<i<<" "<<j<<"b"<<endl;
					dp[i][j]=dp[i-1][j]+cc[i].b;
					rec[i][j][0]=rec[i-1][j][0];
					rec[i][j][1]=rec[i-1][j][1]+1;
				}
			}
		}
		
	/*for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=c;j++)
		cout<<dp[i][j]<<" ";
		cout<<endl;
	}*/
	cout<<dp[n][c];
	
}