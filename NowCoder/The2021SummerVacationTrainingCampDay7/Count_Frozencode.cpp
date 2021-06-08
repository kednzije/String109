#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e6+10,P=998244353,P1=3,P2=332748118;
ll prime[N];
ll factor[110][2];ll facnt;
void getPrime() {
    memset(prime,0,sizeof(prime));
    for(int i=2;i<N;i++) {
        if(!prime[i]) prime[++prime[0]] = i;
        for(int j=1;j<=prime[0]&&prime[j]*i<N;j++) {
            prime[prime[j]*i] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
void getFactor(ll p) {
    facnt = 0;
    ll tmp = p;
    for(int i=1;prime[i]*prime[i]<=tmp;i++) {
        factor[facnt][1] = 0;
        if(tmp % prime[i] == 0) {
            factor[facnt][0] = prime[i];
            while(tmp % prime[i] == 0) {
                factor[facnt][1]++;
                tmp /= prime[i];
            }
            facnt++;
        }
    }
    if(tmp != 1) {
        factor[facnt][0] = tmp;
        factor[facnt++][1] = 1;
    }
}
ll power(ll a,ll b,ll mod) {
    ll res = 1;
    a %= mod;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll getRoot(ll p) {
    ll fip = p-1;
    if(p == 2) return 1;
    getFactor(fip);
    for(ll g=2;g<p;g++) {
        bool flag = true;
        for(int i=0;i<facnt;i++) {
            ll tmp = fip / factor[i][0];
            if(power(g,tmp,p) == 1) {
                flag = false;
                break;
            }
        }
        if(flag) return g;
    }
}

ll I[N],num[N],arr[N],m,myp,c[N],res;
ll lena,lenb,n=1,lim,r[N];
ll a[N],b[N];
ll rpow(ll x,ll y){//要手打
    ll res=1;
    while(y){
        if(y&1)res=(res*x)%P;
        x=(x*x)%P;
        y>>=1;
    }
    return res%P;
}
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void NTT(ll *A,int tp){
    for(int i=0;i<n;i++)if(i<r[i])swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1){
        ll W=rpow(tp?P1:P2,(P-1)/(i<<1));//替换成原根
        for(int j=i<<1,k=0;k<n;k+=j){
            ll w=1;
            for(int l=0;l<i;l++,w=(w*W)%P){//注意模数
                int x=A[k+l],y=w*A[k+i+l]%P;
                A[k+l]=(x+y)%P;
                A[k+i+l]=(x-y+P)%P;
            }
        }
    }
}
int main(){
    getPrime();
    m=read();
    myp=1000003;
    ll g = getRoot(myp);
    ll tmp = 1;
    for(int i=1;i<myp;i++) {
        tmp = tmp * g % myp;
        I[tmp] = i;
    }
    I[1] = 0;
    for(int i=0;i<m;i++) {
        arr[i]=read();
        num[I[arr[i]]]++;
        //cout << I[arr[i]] << " " << num[I[arr[i]]]<< endl;
    }
    lena=myp-1;lenb=myp-1;
    while(n<=lena+lenb)n<<=1,lim++;
    for(int i=0;i<=lena;i++)a[i]=(num[i]+P)%P;
    for(int i=0;i<=lenb;i++)b[i]=(num[i]+P)%P;
    //for(int i=0; i <= m; i++) cout << a[i] << " " << b[i] << endl;
    for(int i=0;i<n;i++)r[i]=(r[i>>1]>>1)|((i&1)<<(lim-1));
    NTT(a,1);
    NTT(b,1);
    for(int i=0;i<=n;i++)a[i]=(a[i]*b[i])%P;
    NTT(a,0);
    ll inv=rpow(n,P-2);
    for(int i=0;i<myp;i++)a[i]=(a[i]*inv)%P;
    for(int i=0;i<m;i++)res+=a[I[arr[i]]];
    cout << res;
}