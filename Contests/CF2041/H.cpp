#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int N=1e6+9;

int f[N][2],s[N][2],n,k;
int fac[N],ifac[N];
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void Init(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=QPow(fac[n],mod-2);
    for(int i=lim-1;~i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
    if(y>x) return 0;
    else return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

signed main(){
    cin>>n>>k;
    n--;
    s[0][1]=s[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int p:{0,1}){
            if(i>=k) f[i][p]=(s[i-1][p^1]-s[i-k][p^1]+mod)%mod;
            else f[i][p]=s[i-1][p^1];
            s[i][p]=(s[i-1][p]+f[i][p])%mod;
        }
    }

    Init(n);
    int ans=1;
    for(int i=1;i<=n;i++){
        ans=((f[i][0]+f[i][1])%mod*C(n,i)%mod+ans)%mod;
        // cout<<f[i][0]<<' '<<f[i][1]<<' '<<C(n,i)<<endl;
    }
    cout<<ans<<endl;

    return 0;
}