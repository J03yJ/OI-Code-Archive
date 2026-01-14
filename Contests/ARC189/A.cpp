#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int N=1e6+9;
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int a[N],n;
int fac[N],ifac[N],ofac[N];
void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
    ifac[lim]=QPow(fac[lim],mod-2);
    for(int i=lim-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
    ofac[1]=1;
    for(int i=2;i<=lim;i++) ofac[i]=ofac[i-2]*i%mod;
}
int C(int n,int m){return fac[n]*ifac[m]%mod*ifac[n-m]%mod;}

signed main(){
    Init(1e6);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    if(a[1]==0){
        cout<<0<<endl;
        return 0;
    }

    int ans=1,cnt=0;
    for(int i=1,j=1;i<=n;i=j){
        while(j<=n&&a[j]==a[i]) j++;
        if(i+1==j) continue ;
        int len=j-i,t=(len-1)/2;
        ans=ans*ofac[len-2]%mod;
        cnt+=t;
        ans=ans*C(cnt,t)%mod;
    }

    cout<<ans<<endl;

    return 0;
}