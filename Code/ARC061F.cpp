#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int fac[N],ifac[N];
inline void InitFac(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
    if(m>n||m<0) return 0;
    else return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

signed main(){
    int n,m,k;
    cin>>n>>m>>k;

    InitFac(n+m+k);
    int ans=0,sum=1;
    for(int s=0;s<=m+k;s++){
        AddAs(ans,Mul(Mul(sum,C(n-1+s,s)),QPow(3,m+k-s)));
        AddAs(sum,sum);
        if(s>=m) SubAs(sum,C(s,m));
        if(s>=k) SubAs(sum,C(s,s-k));
    }
    
    cout<<ans<<endl;

    return 0;
}